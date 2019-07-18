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
* \brief OAL memory allocation implementation for Linux (contiguous allocator)
* \author Rostislav Hulik
* \version
* \date
****************************************************************************/

#include "oal_memory_driver_if.h"

#include <sys/ioctl.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

/////////////////////////////////////////////////////////////////////////
/// Initializes OAL
/////////////////////////////////////////////////////////////////////////
int32_t OAL_Initialize()
{
  printf("OAL Memory allocation functionality not available in INTEGRITY.\n");
  return OAL_FAILURE;
}

/////////////////////////////////////////////////////////////////////////
/// Deinitializes OAL
/////////////////////////////////////////////////////////////////////////
int32_t OAL_Deinitialize()
{
  printf("OAL Memory allocation functionality not available in INTEGRITY.\n");
  return OAL_FAILURE;
}

/////////////////////////////////////////////////////////////////////////
/// Returns a number of current allocations from all processes
/////////////////////////////////////////////////////////////////////////
uint64_t OAL_ContAllocGetNumAllocations()
{
  printf("OAL Memory allocation functionality not available in INTEGRITY.\n");
  return 0;
}

/////////////////////////////////////////////////////////////////////////
/// Returns a number of current mappings from all processes
/////////////////////////////////////////////////////////////////////////
uint64_t OAL_ContAllocGetNumMappings()
{
  printf("OAL Memory allocation functionality not available in INTEGRITY.\n");
  return 0;
}

/////////////////////////////////////////////////////////////////////////
/// Allocates a block of memory with specified size and alignment
/// Uses underlying oal kernel module to do so
/////////////////////////////////////////////////////////////////////////
void * OAL_ContAllocAlloc(uint64_t size, uint64_t align, uint8_t chunk_id)
{
  printf("OAL Memory allocation functionality not available in INTEGRITY.\n");
  return NULL;
}

/////////////////////////////////////////////////////////////////////////
/// Free mapped memory from underlying oal kernel module
/// If memory lacks the physical pointer (allocated externally), it's freed
/// using free()
/////////////////////////////////////////////////////////////////////////
int32_t OAL_ContAllocFree(void *handle_pointer)
{
  printf("OAL Memory allocation functionality not available in INTEGRITY.\n");
  return OAL_FAILURE;
}

/////////////////////////////////////////////////////////////////////////
/// Returns a buffer of specified type.
/// If type is not specified or cannot be mapped, returns NULL
/////////////////////////////////////////////////////////////////////////
void *OAL_ContAllocGetBuffer(uint64_t handle_pointer, uint64_t type)
{
  printf("OAL Memory allocation functionality not available in INTEGRITY.\n");
  return NULL;
}

/////////////////////////////////////////////////////////////////////////
///
/// Function returns total size in bytes being managed by OAL Memory.
///
/// \return
///    total size in bytes being managed by OAL Memory
/////////////////////////////////////////////////////////////////////////
int64_t OAL_ContAllocGetTotalSize(void)
{
  printf("OAL Memory allocation functionality not available in INTEGRITY.\n");
  return 0;
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
  printf("OAL Memory allocation functionality not available in INTEGRITY.\n");
  return 0;
}

uint8_t OAL_MemoryGetDevicesMask()
{
  printf("OAL Memory allocation functionality not available in INTEGRITY.\n");
  return 0;
}

uint8_t OAL_MemoryGetAutobalanceMask()
{
  printf("OAL Memory allocation functionality not available in INTEGRITY.\n");
  return 0;
}

uint64_t OAL_MemoryGetBase(uint8_t chunk_id)
{
  printf("OAL Memory allocation functionality not available in INTEGRITY.\n");
  return 0;
}

uint64_t OAL_MemoryGetsize(uint8_t chunk_id)
{
  printf("OAL Memory allocation functionality not available in INTEGRITY.\n");
  return 0;
}

/////////////////////////////////////////////////////////////////////////
/// Flushes and invalidates the whole cache
/////////////////////////////////////////////////////////////////////////
void CleanAndInvalidateDCacheAll()
{
  printf("OAL Memory allocation functionality not available in INTEGRITY.\n");
}

/////////////////////////////////////////////////////////////////////////
/// Flushes and invalidates the specified cache
/////////////////////////////////////////////////////////////////////////
void CleanAndInvalidateDCache(void *ptr, uint32_t size)
{
  printf("OAL Memory allocation functionality not available in INTEGRITY.\n");
}

/////////////////////////////////////////////////////////////////////////
/// Invalidates the specified cache
/////////////////////////////////////////////////////////////////////////
void InvalidateDCache(void *ptr, uint32_t size)
{
  printf("OAL Memory allocation functionality not available in INTEGRITY.\n");
}

/////////////////////////////////////////////////////////////////////////
/// Flushes the specified cache
/////////////////////////////////////////////////////////////////////////
void CleanDCache(void *ptr, uint32_t size)
{
  printf("OAL Memory allocation functionality not available in INTEGRITY.\n");
}

int32_t OAL_ContAllocUnmap(void *handle_pointer)
{
  printf("OAL Memory allocation functionality not available in INTEGRITY.\n");
  return OAL_FAILURE;
}
