/*****************************************************************************
*
* NXP Confidential Proprietary
*
* Copyright (c) 2013 Freescale Semiconductor;
* Copyright (c) 2017 NXP;
* All Rights Reserved
*
*****************************************************************************
*
* THIS SOFTWARE IS PROVIDED BY NXP "AS IS" AND ANY EXPRESSED OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL NXP OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*
****************************************************************************/
/**
* \file oal_memory_cont_alloc.cpp
* \brief OAL memory allocation implementation (contiguous allocator)
* \author Rostislav Hulik
* \version
* \date 3-March-2016
****************************************************************************/

#include "oal.h"
#include "oal_memory_driver_if.h"
#include "oal_cma_list.h"
#include "oal_allocation_kernel.h"
#include "oal_allocator.h"
#include "os_oal_check.h"
#include "vdb_log.h"
#include <stdlib.h>
#include <stdio.h>

#ifndef NULL
#define NULL 0
#endif

// Offset of non-cached memory mapping
#define STANDALONE_NON_CACHED_OFFSET 0x100000000
// Offset of cached memory mapping
#define STANDALONE_CACHED_OFFSET     0x00000000

bool ddr_init = false;

uint8_t  oal_allocator_devices = 0;
uint8_t  oal_devices_loaded = 0;
uint8_t  oal_devices_autobalanced = 0;
uint32_t oal_device_alignment[OAL_MAX_ALLOCATOR_NUM] = {0};
#if 0
extern uint64_t oal_alloc_allocated_num[OAL_MAX_ALLOCATOR_NUM];
extern uint64_t oal_alloc_mapped_num[OAL_MAX_ALLOCATOR_NUM];
#endif

OAL_RESULT OAL_InitRegion(uint8_t id, uint64_t base, uint64_t length, uint32_t alignment, uint8_t autobalanced)
{
  oal_devices_loaded |= (1U << id);
  oal_device_alignment[id] = alignment;

  if (autobalanced > 0)
  {
    oal_devices_autobalanced |= 1U << id;
  }
  else
  {
    oal_devices_autobalanced &= ~(1U << id);
  }

  apex_allocator_mmap_init(id, base, length);

  cma_list_init(id, base, base + length, oal_device_alignment[id]);

  ++oal_allocator_devices;

  return OAL_SUCCESS;
}

/////////////////////////////////////////////////////////////////////////
/// Initializes OAL
/////////////////////////////////////////////////////////////////////////
int32_t OAL_Initialize(void)
{
  if (ddr_init == false)
  {
    OAL_InitRegion(0, 0x000000008B000000, 0x0000000005000000, 0x1000, 1); // DDR0
    OAL_InitRegion(1, 0x00000000CB000000, 0x0000000005000000, 0x1000, 1); // DDR1
    OAL_InitRegion(2, 0x000000003E800000, 0x0000000000300000, 0x8, 0); // SRAM singlebanked
    OAL_InitRegion(3, 0x000000003EB00000, 0x0000000000100000, 0x8, 0); // SRAM multibanked
    ddr_init = true;
    vdb_LogInit();      /* enable logging */
  }
  return OAL_SUCCESS;
}

/////////////////////////////////////////////////////////////////////////
/// Deinitializes OAL
/////////////////////////////////////////////////////////////////////////
int32_t OAL_Deinitialize(void)
{
  vdb_LogStop();
  return OAL_SUCCESS;
}

/////////////////////////////////////////////////////////////////////////
/// Returns a number of current allocations from all processes
/////////////////////////////////////////////////////////////////////////
uint64_t OAL_ContAllocGetNumAllocations(void)
{
  uint64_t retval;
  if (ddr_init)
  {
    retval = oal_get_num_allocations();
  }
  else
  {
    VDB_LOG_ERROR("OAL: Initialization failed. Please check the OAL initialization.\n");
    retval = 0xFFFFFFFFFFFFFFFF;
  }
  return retval;
}

/////////////////////////////////////////////////////////////////////////
/// Returns a number of current mappings from all processes
/////////////////////////////////////////////////////////////////////////
uint64_t OAL_ContAllocGetNumMappings(void)
{
  uint64_t retval;
  if (ddr_init)
  {
    retval = oal_get_num_mappings();
  }
  else
  {
    VDB_LOG_ERROR("OAL: Initialization failed. Please check the OAL initialization.\n");
    retval = 0xFFFFFFFFFFFFFFFF;
  }
  return retval;
}

/////////////////////////////////////////////////////////////////////////
/// Allocates a block of memory with specified size and alignment
/////////////////////////////////////////////////////////////////////////
void * OAL_ContAllocAlloc(uint64_t size, uint64_t align, uint8_t chunk_id)
{
  void *retval = 0;
  if (ddr_init)
  {
    retval = (void *)oal_alloc(size, align, chunk_id, 0);
  }
  else
  {
    VDB_LOG_ERROR("OAL: Initialization failed. Please check the OAL initialization.\n");
  }

  return retval;
}

/////////////////////////////////////////////////////////////////////////
/// Free mapped memory from underlying oal kernel module
/// If memory lacks the physical pointer (allocated externally), it's freed
/// using free()
/////////////////////////////////////////////////////////////////////////
int32_t OAL_ContAllocFree(void *handle_pointer)
{
  int32_t retval = OAL_SUCCESS;
  if (ddr_init)
  {
    ///////////////////////////////////////////////
    // SAFE SECTION

    // Free the memory
    handle_pointer = (void*)oal_free((uint64_t)handle_pointer);

    if (handle_pointer != 0)
    {
      retval = OAL_FAILURE;
    }
    ///////////////////////////////////////////////
    // END SAFE SECTION
  }
  else
  {
    VDB_LOG_ERROR("OAL: Initialization failed. Please check the OAL initialization.\n");
    retval = OAL_FAILURE;
  }
  return retval;
}

int32_t OAL_ContAllocUnmap(void *handle_pointer)
{
  int32_t retval = OAL_SUCCESS;
  if (ddr_init)
  {
    oal_unmap((uint64_t)handle_pointer);
  }
  else
  {
    VDB_LOG_ERROR("OAL: Initialization failed. Please check the OAL initialization.\n");
    retval = OAL_FAILURE;
  }
  return retval;
}

/////////////////////////////////////////////////////////////////////////
/// Returns a buffer of specified type.
/// If type is not specified or cannot be mapped, returns NULL
/////////////////////////////////////////////////////////////////////////
void *OAL_ContAllocGetBuffer(uint64_t handle_pointer, uint64_t type)
{
  void *vadr = 0;
  if (ddr_init)
  {
    ///////////////////////////////////////////////
    // SAFE SECTION
    uint64_t mappings[6];
    oal_getmappingshw((uint64_t) handle_pointer, mappings);

    // if NCH_NB wasn't mapped yet and we want it (and we can, ACCESS_PHY exists), we map it from non-cached file
    if ((mappings[type] == 0) && (mappings[ACCESS_PHY] != 0))
    {
      bool ok = true;
      for (int32_t i = 1; i < ACCESS_NUM; ++i)
      {
        if (mappings[i] != 0)
        {
          VDB_LOG_WARNING("OAL: Multiple memory mappings detected. Please consider revision of the code to prevent different caching settings.\n");
          ok = false;
          break;
        }
      }

      if (ok)
      {
        if ((type == ACCESS_NCH_NB) || (type == ACCESS_NCH_B))
        {
          vadr = (void *)(handle_pointer + STANDALONE_NON_CACHED_OFFSET);
        }
        else if  ((type == ACCESS_CH_WB) || (type == ACCESS_CH_WT))
        {
          vadr = (void *)(handle_pointer + STANDALONE_CACHED_OFFSET);
        }
        else
        {
            vadr = 0;
        }

        if (vadr)
        {
          if (!(bool)oal_map_phys(handle_pointer, type, (uint64_t)vadr))
          {
            vadr = 0;
          }
        }
      }
    }
    else
    {
      vadr = (void *)mappings[type];
    }
    ///////////////////////////////////////////////
    // SAFE SECTION
  }
  else
  {
    VDB_LOG_ERROR("OAL: Initialization failed. Please check the OAL initialization.\n");
  }
  return vadr;
}

////////////////////////////////////////////////////////////////////////
///
/// Function returns total size in bytes being managed by OAL Memory.
///
/// \return
///    total size in bytes being managed by OAL Memory
/////////////////////////////////////////////////////////////////////////
int64_t OAL_ContAllocGetTotalSize(void)
{
  int64_t retval = -1;
  if (ddr_init)
  {
    retval = oal_memorysizetotal();
  }
  else
  {
    VDB_LOG_ERROR("OAL: Initialization failed. Please check the OAL initialization.\n");
  }
  return retval;
}

/////////////////////////////////////////////////////////////////////////
///
/// Function returns free size in bytes remaining in OAL Memory.
///
/// \return
///    free size in bytes remaining in OAL Memory
/////////////////////////////////////////////////////////////////////////
int64_t OAL_ContAllocGetFreeSize(void)
{
  int64_t retval = -1;
  if (ddr_init)
  {
    retval = oal_memorysizefree();
  }
  else
  {
    VDB_LOG_ERROR("OAL: Initialization failed. Please check the OAL initialization.\n");
  }
  return retval;
}

uint8_t OAL_MemoryGetDevicesMask(void)
{
  uint8_t retval = 0;
  if (ddr_init)
  {
    retval = oal_devices_loaded;
  }
  else
  {
    VDB_LOG_ERROR("OAL: Initialization failed. Please check the OAL initialization.\n");
  }
  return retval;
}

uint8_t OAL_MemoryGetAutobalanceMask(void)
{
  uint8_t retval = 0;
  if (ddr_init)
  {
    retval = oal_devices_autobalanced;
  }
  else
  {
    VDB_LOG_ERROR("OAL: Initialization failed. Please check the OAL initialization.\n");
  }
  return retval;
}

uint64_t OAL_MemoryGetBase(uint8_t chunk_id)
{
  uint64_t retval = 0;
  if (ddr_init)
  {
    retval = apex_allocator_get_physical_base(chunk_id);
  }
  else
  {
    VDB_LOG_ERROR("OAL: Initialization failed. Please check the OAL initialization.\n");
  }
  return retval;
}

uint64_t OAL_MemoryGetsize(uint8_t chunk_id)
{
  uint64_t retval = 0;
  if (ddr_init)
  {
    retval = apex_allocator_get_total_size(chunk_id);
  }
  else
  {
    VDB_LOG_ERROR("OAL: Initialization failed. Please check the OAL initialization.\n");
  }
  return retval;
}
