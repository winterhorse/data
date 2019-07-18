/*
 * Copyright (c) 2014 Freescale Semiconductor
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "oal_allocator.h"
#include "oal_cma_list.h"
#include "oal_allocation_kernel.h"
#include "oal_debug_out.h"
#include "oal_allocator_defines.h"
#include "oal_chunk_ids.h"
#include "oal_kalloc.h"

extern uint8_t  oal_allocator_devices;
extern uint8_t  oal_devices_loaded;
extern uint8_t  oal_devices_autobalanced;
extern uint32_t oal_device_alignment[OAL_MAX_ALLOCATOR_NUM];

uint64_t oal_alloc_allocated_num[OAL_MAX_ALLOCATOR_NUM] = {0};
uint64_t oal_alloc_mapped_num[OAL_MAX_ALLOCATOR_NUM] = {0};

/////////////////////////////////////////////////////////////////////////
/// Allocates a block of memory with specified size and alignment
/// Uses underlying oal kernel module to do so
/////////////////////////////////////////////////////////////////////////
uint64_t oal_alloc(uint64_t size, uint64_t align, uint8_t chunk_id, int32_t pid)
{
  uint64_t retval = 0;

  t_MemArea *area;

  // if size is 0, return error
  if (size)
  {
    // Find specific chunk id to allocate and do it
    if (chunk_id < OAL_CHUNK_ID_MAXNR)
    {
      if ((oal_devices_loaded & (1U << chunk_id)) != 0)
      {
        if (align < oal_device_alignment[chunk_id]) {
          align = oal_device_alignment[chunk_id];
        }

        oal_printk("     Trying to alloc specific chunk (%X). Size: %llX, alignment: %llX\n",
                   chunk_id, size, align);

        retval = (uint64_t)apex_allocator_malloc(chunk_id, size, align);
      }
    }
    else if (chunk_id == 0xFF)   /* up to OAL to decide */
    {
      // copy autobalanced flags
      uint8_t oal_devices_autobalanced_local = oal_devices_autobalanced;

      // while there are some autobalanced chunks free

      oal_printk("     Starting search for the best chunk.\n");

      while (oal_devices_autobalanced_local > 0)
      {
        uint32_t i;
        int32_t min_allocations = 0xFFFFFFFF;

        // search autobalanced chunk which has the least number of allocations
        for (i = 0; i < OAL_MAX_ALLOCATOR_NUM; ++i)
        {
          if (((oal_devices_autobalanced_local & (1U << i)) != 0) &&
              (oal_alloc_allocated_num[i] < (uint64_t)min_allocations))
          {
            min_allocations = oal_alloc_allocated_num[i];
            chunk_id = i;
          }
        }
        // set this chunk for not using in next search
        oal_devices_autobalanced_local &= ~(1U << chunk_id);

        // try to allocate
        if (align < oal_device_alignment[chunk_id]) {
          align = oal_device_alignment[chunk_id];
        }

        oal_printk("       Trying to alloc chunk (%X). Size: %llX, alignment: %llX\n",
                   chunk_id, size, align);

        retval = (uint64_t)apex_allocator_malloc(chunk_id, size, align);

        // if succeeded, break, search the rest otherwise
        if (retval) {
            break;
        }
      }
    }
    else    /* illegal chunk_id */
    {
        retval = 0;
    }

    // If allocation succeeded
    if (retval)
    {
      oal_printk("     Success, saving into list.\n");

      area = (t_MemArea *)OAL_Kalloc(sizeof(t_MemArea), VIRT_MEM);

      // Create an allocation structure
      area->address[ACCESS_PHY] = retval;
      area->size = size;
      area->chunk_id = chunk_id;
      area->address[ACCESS_CH_WB] = 0;
      area->address[ACCESS_CH_WT] = 0;
      area->address[ACCESS_NCH_B] = 0;
      area->address[ACCESS_NCH_NB] = 0;
      area->pid = pid;

      // Push it into the list of allocations
      if (cma_list_area_push_back(area) >= 0)
      {
        ++oal_alloc_allocated_num[chunk_id];
      }
      else {
        retval = 0;
      }
    }
  }

  return retval;
}

//////////////////////////////////////////////////////////////////////////////////
// Function removes a contiguous memory block and removes an entry from the management list.
// Returns 0 if success and ULONG_MAX if fail.
// Does not free virtual mappings.
//////////////////////////////////////////////////////////////////////////////////
uint64_t oal_free (uint64_t handle_pointer)
{
  t_MemArea *area;
  int32_t ret;
  uint64_t retval;

  oal_printk("     Freeing list entry %llX.\n", handle_pointer);
  // Get area from list and try to remove it
  area = cma_list_area_find(handle_pointer);
  ret = cma_list_area_remove(area);


  // If successfully removed
  if ((ret > 0) && ((bool)area))
  {
    oal_printk("     Freeing memory %llX.\n", area->address[ACCESS_PHY]);

    // Free allocated memory and free the structure
    apex_allocator_free(area->chunk_id, (void *)area->address[ACCESS_PHY]);
    --oal_alloc_allocated_num[area->chunk_id];
    OAL_Kfree(area, VIRT_MEM);
    retval = 0;
  }
  else
  {
    retval = ULONG_MAX;
  }
  return retval;
}


uint64_t oal_free_phys (uint64_t physical_pointer)
{
  return oal_free(physical_pointer);
}

uint64_t oal_unmap (uint64_t handle_pointer)
{
  t_MemArea *area;


  oal_printk("     Unmapping the pointer %llX.\n", handle_pointer);

  area = cma_list_area_find(handle_pointer);
  memset(&(area->address[1]), 0, 32);

  return 0;
}

//////////////////////////////////////////////////////////////////////////////////
// Function returns number of allocations.
//////////////////////////////////////////////////////////////////////////////////
uint64_t oal_get_num_allocations (void)
{
  int32_t i;
  int32_t num_allocs = 0;
  for (i = 0; i < OAL_MAX_ALLOCATOR_NUM; ++i)
  {
    num_allocs += oal_alloc_allocated_num[i];
  }
  return num_allocs;
}

//////////////////////////////////////////////////////////////////////////////////
// Function returns number of mappings.
//////////////////////////////////////////////////////////////////////////////////
uint64_t oal_get_num_mappings (void)
{
  int32_t i;
  int32_t num_mappings = 0;
  for (i = 0; i < OAL_MAX_ALLOCATOR_NUM; ++i)
  {
    num_mappings += oal_alloc_mapped_num[i];
  }

  return num_mappings;
}


//////////////////////////////////////////////////////////////////////////////////
// Function returns a size of allocated memory block.
//////////////////////////////////////////////////////////////////////////////////
uint64_t oal_getsize(uint64_t handle_pointer)
{
  t_MemArea *area;
  uint64_t retval;

  area = cma_list_area_find(handle_pointer);

  if (area)
  {
    oal_printk("     Returned allocated size: %llX\n", area->size);
    retval = area->size;
  }
  else {
    retval = 0;
  }
  return retval;
}

void oal_getmappings(uint64_t handle_pointer, uint64_t mappings[ACCESS_NUM+1])
{
  t_MemArea *area;
  int32_t i;
  area = cma_list_area_find(handle_pointer);
  if (area)
  {
    oal_printk("     Memory mappings available:\n");
    for (i = 0; i < ACCESS_NUM; ++i)
    {
      oal_printk("       %i: %llX\n", i, area->address[i]);
      mappings[i] = area->address[i];
    }
    mappings[ACCESS_NUM] = area->size;
  }
  else
  {
    for (i = 0; i < ACCESS_NUM; ++i) {
      mappings[i] = 0;
    }
    mappings[ACCESS_NUM] = 0;
  }
}

void oal_getmappingshw(uint64_t handle_pointer, uint64_t mappings[ACCESS_NUM+1])
{
  oal_getmappings(handle_pointer, mappings);
}

//////////////////////////////////////////////////////////////////////////////////
// Function returns a current process virtual memory mapping.
//////////////////////////////////////////////////////////////////////////////////
uint64_t oal_getbuffer(uint64_t handle_pointer, uint64_t type)
{
  t_MemArea *area;
  uint64_t retval;

  area = cma_list_area_find(handle_pointer);

  // if found appropriate area, try to find an vaddress
  if (area)
  {
    oal_printk("     Returned mapped address: %llX\n", area->address[type]);
    retval = area->address[type];
  }
  else {
    retval = 0;
  }
  return retval;
}

//////////////////////////////////////////////////////////////////////////////////
// Function adds a new memory mapping into the management list (current process).
//////////////////////////////////////////////////////////////////////////////////
uint64_t oal_map(uint64_t handle_pointer, uint64_t type, uint64_t virtual_pointer)
{
  t_MemArea *area;
  area = cma_list_area_find(handle_pointer);
  area->address[type] = virtual_pointer;

  oal_printk("     Added mapping based on virtual address: %llX[%lli] ->: %llX\n", handle_pointer, type, virtual_pointer);

  return virtual_pointer;
}

uint64_t oal_map_new(uint64_t type, uint64_t virtual_pointer, uint64_t size, int32_t pid)
{
  int32_t i;
  int32_t ret;
  uint64_t retval;

  t_MemArea *area = (t_MemArea *)OAL_Kalloc(sizeof(t_MemArea), VIRT_MEM);

  oal_printk("     Added new allocation outside OAL. Type: %llX, %llX@%llX\n", size, type, virtual_pointer);
  // Create an allocation structure
  area->address[type] = virtual_pointer;
  area->size = size;
  area->pid = pid;

  for (i = 0; i < ACCESS_NUM; ++i) {
    if (i != (int32_t)type) {
        area->address[i] = 0;
    }
  }

  // Push it into the list of allocations
  oal_printk("     Adding into list of allocations\n");
  ret = cma_list_area_push_back(area);
  #if 0
  ++oal_alloc_allocated_num;
  #endif

  if (ret < 0) {
    retval = 0;
  }
  else {
    retval = (uint64_t)virtual_pointer;
  }
  return retval;
}

//////////////////////////////////////////////////////////////////////////////////
// Function adds a new memory mapping into the management list (current process).
//////////////////////////////////////////////////////////////////////////////////
uint64_t oal_map_phys(uint64_t physical_pointer, uint64_t type, uint64_t virtual_pointer)
{
  t_MemArea *area;
  area = cma_list_area_find(physical_pointer);
  area->address[type] = virtual_pointer;
  #if 0
  ++oal_alloc_mapped_num;
  #endif

  oal_printk("     Added mapping based on physical address: %llX[%lli] ->: %llX\n", physical_pointer, type,  virtual_pointer);

  return virtual_pointer;
}

//////////////////////////////////////////////////////////////////////////////////
// Function returns total size in bytes being managed by OAL Memory.
//////////////////////////////////////////////////////////////////////////////////
int64_t oal_memorysizetotal(void)
{
  uint64_t lSizeInBytes = 0;
  uint32_t i;

  for (i = 0; i < OAL_MAX_ALLOCATOR_NUM; ++i)
  {
    if ((oal_devices_loaded & (1U << i)) != 0)
    {
      lSizeInBytes += apex_allocator_get_total_size(i);
    }
  }

  oal_printk("     Returned %llX Bytes\n", lSizeInBytes);
  return lSizeInBytes;
}

//////////////////////////////////////////////////////////////////////////////////
// Function returns free size in bytes remaining in OAL Memory.
//////////////////////////////////////////////////////////////////////////////////
int64_t oal_memorysizefree(void)
{
  uint64_t lSizeInBytes = 0;
  uint32_t i;

  for (i = 0; i < OAL_MAX_ALLOCATOR_NUM; ++i)
  {
    if ((oal_devices_loaded & (1U << i)) != 0)
    {
      lSizeInBytes += apex_allocator_get_free_size(i);
    }
  }

  oal_printk("     Returned %llX Bytes\n", lSizeInBytes);
  return lSizeInBytes;
}

/* function to get memory information */
uint8_t oal_get_chunkid(uint64_t handle_pointer)
{
    uint8_t retval;
    t_MemArea *area;
    area = cma_list_area_find(handle_pointer);

    /* return an invalid area ID */
    if (area == NULL) {
        retval = OAL_MAX_ALLOCATOR_NUM + 1;
    }
    else {
        retval = area->chunk_id;
    }
    return retval;
}

uint64_t OAL_KernelMemoryFree(void *physical_pointer)
{
  return oal_free((uint64_t)physical_pointer);
}
