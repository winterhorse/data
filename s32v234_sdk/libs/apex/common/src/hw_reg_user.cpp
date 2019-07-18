/*****************************************************************************
*
* Freescale Confidential Proprietary
*
* Copyright (c) 2014 Freescale Semiconductor;
* All Rights Reserved
*
*****************************************************************************
*
* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*
****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <hw_reg_user.h>
#include <apex_642cl_map.h>

static
unsigned long gsVirtualHwPtrArray [HW_REG_NUM] = { 0 };

static
unsigned char gsVirtualMappingComplete = 0;

static
const
unsigned long gsPhysicalHwPtrArray[HW_REG_NUM][2] =
{
   {APEX_642CL_SMEM_BASE_ADDRESS,         0xFFFF},  // HW_REG_SMEM

   {APEX_642CL_MCDMA_BASE_ADDRESS + 0x00100000,        0xFFFF},  // HW_REG_MCDMA (+ 0x00100000 results in alias that is NOT a posted write for a register)
   {APEX_642CL_MOTION_COMP_BASE_ADDRESS,  0xFFFF},  // HW_REG_MODMA
   {APEX_642CL_STREAM_DMA_BASE_ADDRESS,   0xFFFF},  // HW_REG_STIO
   {APEX_642CL_SEQ_BASE_ADDRESS,          0xFFFF},  // HW_REG_USEQ
   {APEX_642CL_GLOBAL_BASE_ADDRESS,       0xFFFF},  // HW_REG_GLOBAL
   {APEX_642CL_HOST_DEBUG_BASE_ADDRESS,   0xFFFF},  // HW_REG_DEBUG
   {APEX_642CL_DMEM_FIFO_0_BASE_ADDRESS,  0xFFFF},  // HW_REG_DMEM_FIFO_0
   {APEX_642CL_DMEM_FIFO_1_BASE_ADDRESS,  0xFFFF},  // HW_REG_DMEM_FIFO_1
   {APEX_642CL_CMEM_IF_BASE_ADDRESS,      0xFFFF},  // HW_REG_CMEM_IF
   {APEX_642CL_HRSZ_BASE_ADDRESS,         0xFFFF},  // HW_REG_HOR_RESIZER

   {APEX_642CL_CMEM_BASE_ADDRESS,            0x40000}, // HW_REG_CMEM_GOC_63_00

   {APEX_642CL_CMEM_BASE_ADDRESS+0x00080000, 0x40000}, // HW_REG_CMEM_SOC_31_00 & HW_REG_CMEM_SOC_63_32
   {APEX_642CL_CMEM_BASE_ADDRESS+0x00100000, 0x40000}, // HW_REG_CMEM_SOC_63_00

   {APEX_642CL_CMEM_BASE_ADDRESS+0x00300000, 0x40000}, // HW_REG_CMEM_BOC_31_00
   {APEX_642CL_CMEM_BASE_ADDRESS+0x00310000, 0x40000}, // HW_REG_CMEM_BOC_63_32
   {APEX_642CL_CMEM_BASE_ADDRESS+0x00340000, 0x40000}  // HW_REG_CMEM_BOC_63_00
};

int MapPhysicalToVirtual(unsigned long lPhysicalAddr, unsigned long /*lSizeInBytes*/, unsigned long &lVirtualAddr)
{
   lVirtualAddr = lPhysicalAddr;
   return 0;
}

int UnmapVirtualHwPtrArray()
{
   for (int i = 0; i < HW_REG_NUM; i++)
   {
      if (gsVirtualHwPtrArray[i] != 0)
      {
         gsVirtualHwPtrArray[i] = 0;
      }
   }

   return 0;
}

int InitVirtualHwPtrArray()
{
   int rVal = 0;

   if (0 == gsVirtualMappingComplete)
   {
      for (int i = 0; i < HW_REG_NUM; i++)
      {
         rVal = MapPhysicalToVirtual(
            gsPhysicalHwPtrArray[i][0], //physical address
            gsPhysicalHwPtrArray[i][1], //desired size in bytes
            gsVirtualHwPtrArray [i]);   //resulting virtual address
         if (rVal)
         {
            break;
      }
   }
   }
   
   if (0 == rVal)
   {
      gsVirtualMappingComplete = 1;
   }
   else
   {
      UnmapVirtualHwPtrArray();
   }
   
   return rVal;
}

void* ReturnVirtualHwPtr (int lApexID, HW_REG_ID lHwRegId)
{
   return (void*)gsVirtualHwPtrArray[lHwRegId];
}

void* ReturnPhysicalHwPtr (int lApexID, HW_REG_ID lHwRegId)
{
   return (void*)gsPhysicalHwPtrArray[lHwRegId][0];
}
