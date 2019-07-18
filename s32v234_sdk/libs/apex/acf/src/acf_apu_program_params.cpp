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
#include <acf_apu_program_params.h>
#include <string.h>
#include <acf_datadesc.hpp>
#include <stdio.h>

#if defined(__STANDALONE__) && defined(__ARMV8)
	//#include <printf.h>
#endif

#define DEBUG_IODUMP 0
#if (DEBUG_IODUMP)
const uint32_t gExtMemBaseAddr = 0x30000000; //value set to be friendly to HW simulation
#endif

using namespace std;

//Use this method to see if a 1D processing pipeline can be established
//NOTE: 1D in this case refers to whether or not is a 1D or 2D 'array of chunks'
//(e.g. if input is a 640x16 region and the chunk size is 16x16 we would have a 1D list of 16x16 chunks,
//      whereas if input is a 640x32 region and chunk size is 16x16, we would have a 2D array of 16x16 chunks
//***This function requires that chunk size has already been chosen!!!
int32_t CheckIf1D_pipeline (std::vector<ACF_Process_PortInfo> &lPortInfoVec)
{
   int lFlag1D = 1; //initialized to 1; it will be set to 0 if a 2D input is encountered

   for (int32_t i=0; i<(int32_t)lPortInfoVec.size(); i++)
   {
      ACF_Process_PortInfo* lpPortInfo = &lPortInfoVec[i];

      //can only be considered 1D if ALL inputs are 1D; set 'lFlag1D' to zero if a 2D input is encountered
      if (lpPortInfo->IsInput())
      {
         if (lpPortInfo->IsDirect() && (lpPortInfo->mDataDesc.RetHeight() > lpPortInfo->mChunkHeight))
         {
            lFlag1D = 0;
            break;
         }
         else if (lpPortInfo->IsIndirect() && (lpPortInfo->mOffsetArray.RetHeight() > 1))
         {
            lFlag1D = 0;
            break;
         }
      }
   }

   return lFlag1D;
}

void CalcCoreParameters_NumIterations(ACF_Process_PortInfo* lpPortInfo,
                                     ACF_Process_PortInfo_APU* lpPortInfoApu,
                                     int32_t lRoiInfoT,
                                     int32_t lRoiInfoB,
                                     int32_t lApuArrayWidth,
                                     int32_t lFlag1D,
                                     int32_t& lNumInputIterations,
                                     int32_t& lNumOutputIterations)
{
   //NOTE: if data sizes are not divisible by chunk size, the number of calculated iterations will be rounded up
   //NOTE: It is assumed that the port being analyzed is a non-static input

   ACF_DataDesc* lpDD = &lpPortInfo->mDataDesc;

   if (lpPortInfoApu->IsCmem())
   {
      if (lpPortInfo->IsDirect())
      {
         //---------------------
         //nonstatic direct cmem
         //---------------------

         if (lFlag1D) //1D case (i.e. 1D array of chunks)
         {
            int32_t lNumChunks = (lpDD->RetWidth() + lpPortInfo->mChunkWidth - 1)/lpPortInfo->mChunkWidth;
            lNumInputIterations = (lNumChunks + lApuArrayWidth - 1)/lApuArrayWidth;
            lNumOutputIterations = lNumInputIterations;
         }
         else //2D case
         {
               //adjust input iterations for ROI (it is currently assumed that ROIs are nicely located and requirements
               //for additional data are met by transferring the fewest number of FULL CHUNKS/TILES)
               int32_t lRoiTilesT  = (lRoiInfoT + lpPortInfo->mChunkHeight - 1)/lpPortInfo->mChunkHeight;
               lNumInputIterations = (lpDD->RetHeight() + lRoiInfoB + lpPortInfo->mChunkHeight - 1)/lpPortInfo->mChunkHeight + lRoiTilesT;
               lNumOutputIterations = (lpDD->RetHeight() + lpPortInfo->mChunkHeight - 1)/lpPortInfo->mChunkHeight;
         }
      }
      else if (lpPortInfo->IsIndirect())
      {
         //-----------------------------
         //nonstatic indirect cmem input
         //-----------------------------

         if (lFlag1D) //1D case (i.e. 1D list of chunks)
         {
            lNumInputIterations = (lpPortInfo->mOffsetArray.RetWidth() + lApuArrayWidth - 1)/lApuArrayWidth;
            lNumOutputIterations = lNumInputIterations;
         }
         else //2D case
         {
            lNumInputIterations = lpPortInfo->mOffsetArray.RetHeight();
            lNumOutputIterations = lNumInputIterations;
         }
      }
   }
   else if (lpPortInfoApu->IsDmem())
   {
      //--------------------
      //nonstatic dmem input
      //--------------------

      if (lFlag1D) //1D case
      {
         lNumInputIterations = (lpDD->RetWidth() + lpPortInfo->mChunkWidth - 1)/lpPortInfo->mChunkWidth;
         lNumOutputIterations = lNumInputIterations;
      }
      else //2D case
      {
            lNumInputIterations = (lpDD->RetHeight() + lpPortInfo->mChunkHeight - 1)/lpPortInfo->mChunkHeight;
            lNumOutputIterations = lNumInputIterations;
      }
   }
}

void CalcCoreParameters_TileInfo(ACF_Process_PortInfo* lpPortInfo,
                                 ACF_Process_PortInfo_APU* /*lpPortInfoApu*/,
                                int32_t lRoiInfoL,
                                int32_t lRoiInfoR,
                                int32_t lRoiInfoT,
                                int32_t lApuArrayWidth,
                                int32_t lFlag1D,
                                int32_t& lInputTileWidthInChunks,
                                int32_t& lLastInputTileWidthInChunks,
                                int32_t& lOutputTileWidthInChunks,
                                int32_t& lLastOutputTileWidthInChunks,
                                int32_t& lStartCuAdjForRoi,
                                int32_t& lOutputSkip,
                                int32_t& lIOWidthInChunks1D)
{
   //NOTE: tile widths (in chunks) are rounded up if data width is not nicely divisible by chunk width
   //NOTE: It is assumed that the port being analyzed is a cmem input

   if (lpPortInfo->IsDirect())
   {
      //---------------------------
      //direct cmem input
      //---------------------------

      ACF_DataDesc* lpDD = &lpPortInfo->mDataDesc;

      if (lFlag1D) //1D case
      {
         //tile will always span CU array (except for 'last' tile which may be smaller)
         int32_t lNumChunks = (lpDD->RetWidth() + lpPortInfo->mChunkWidth - 1)/lpPortInfo->mChunkWidth;
         lInputTileWidthInChunks = (lNumChunks < lApuArrayWidth) ? lNumChunks : lApuArrayWidth;
         lLastInputTileWidthInChunks = ((lNumChunks % lApuArrayWidth)!= 0) ? (lNumChunks % lApuArrayWidth) : lApuArrayWidth;
         lOutputTileWidthInChunks = lInputTileWidthInChunks;
         lLastOutputTileWidthInChunks = lLastInputTileWidthInChunks;
         lIOWidthInChunks1D = lNumChunks;
      }
      else //2D case
      {
         //adjust for ROI (it is currently assumed that ROIs are nicely located and requirements
         //for additional data are met by transferring the fewest number of FULL CHUNKS/TILES)
         int32_t lRoiChunksL = (lRoiInfoL + lpPortInfo->mChunkWidth - 1)/lpPortInfo->mChunkWidth;
         int32_t lRoiTilesT  = (lRoiInfoT + lpPortInfo->mChunkHeight - 1)/lpPortInfo->mChunkHeight;

#if 0
         //This code fragment was related to the start of some work towards allowing ROI on non-chunk boundaries but the problem
         //is more complex than anticipated ... parking for now.

         int32_t lRoiTilesB  = (lRoiInfoB + lpPortInfo->mChunkHeight - 1)/lpPortInfo->mChunkHeight;

         //if ROI is NOT nicely chunk aligned, the data transfer will still transfer chunks; in this case adjust the padding offset
         //(within the chunk) to line up with the edge of the useful data (which will not coincide with the chunk edge in this case)
         int32_t lPadChOffsetT = ((lRoiInfoT%lpPortInfo->mChunkHeight) > 0) ? (lpPortInfo->mChunkHeight - (lRoiInfoT%lpPortInfo->mChunkHeight)) : (0);
         int32_t lPadChOffsetB = ((lRoiInfoB%lpPortInfo->mChunkHeight) > 0) ? (lpPortInfo->mChunkHeight - (lRoiInfoB%lpPortInfo->mChunkHeight)) : (0);
         int32_t lPadChOffsetL = ((lRoiInfoL%lpPortInfo->mChunkWidth) > 0) ? (lpPortInfo->mChunkWidth - (lRoiInfoL%lpPortInfo->mChunkWidth)) : (0);
         int32_t lPadChOffsetR = ((lRoiInfoR%lpPortInfo->mChunkWidth) > 0) ? (lpPortInfo->mChunkWidth - (lRoiInfoR%lpPortInfo->mChunkWidth)) : (0);
         lPadChOffsetTBLR = (lPadChOffsetT << 24) | (lPadChOffsetB << 16) | (lPadChOffsetL << 8) | (lPadChOffsetR << 0);

         printf("chunksize=(%dx%x) lRoiInfoTBLR=(%d %d %d %d) offsetTBLR=(%d %d %d %d) extrachunksTBLR=(%d %d %d %d)\n",
               lpPortInfo->mChunkWidth, lpPortInfo->mChunkHeight,
               lRoiInfoT, lRoiInfoB, lRoiInfoL, lRoiInfoR,
               lPadChOffsetT,lPadChOffsetB,lPadChOffsetL,lPadChOffsetR,
               lRoiTilesT, lRoiTilesB, lRoiChunksL, lRoiChunksR);
#endif

         lInputTileWidthInChunks = (lpDD->RetWidth() + lRoiInfoR + lpPortInfo->mChunkWidth - 1)/lpPortInfo->mChunkWidth + lRoiChunksL;
         lLastInputTileWidthInChunks = lInputTileWidthInChunks;
         lOutputTileWidthInChunks = (lpDD->RetWidth() + lpPortInfo->mChunkWidth - 1)/lpPortInfo->mChunkWidth;
         lLastOutputTileWidthInChunks = lOutputTileWidthInChunks;
         lStartCuAdjForRoi = lRoiChunksL;
         lOutputSkip = lRoiTilesT;
      }
   }
   else if (lpPortInfo->IsIndirect())
   {
      //-----------------------------
      //indirect cmem input
      //-----------------------------

      if (lFlag1D) //1D case
      {
         lInputTileWidthInChunks = (lpPortInfo->mOffsetArray.RetWidth() < lApuArrayWidth) ?
                                   lpPortInfo->mOffsetArray.RetWidth() : lApuArrayWidth;
         lLastInputTileWidthInChunks = ((lpPortInfo->mOffsetArray.RetWidth() % lApuArrayWidth) != 0) ?
                                       (lpPortInfo->mOffsetArray.RetWidth() % lApuArrayWidth) : lApuArrayWidth;
         lOutputTileWidthInChunks = lInputTileWidthInChunks;
         lLastOutputTileWidthInChunks = lLastInputTileWidthInChunks;
         lIOWidthInChunks1D = lpPortInfo->mOffsetArray.RetWidth();
      }
      else //2D case
      {
         lInputTileWidthInChunks  = lpPortInfo->mOffsetArray.RetWidth();
         lLastInputTileWidthInChunks = lInputTileWidthInChunks;
         lOutputTileWidthInChunks = lInputTileWidthInChunks;
         lLastOutputTileWidthInChunks = lOutputTileWidthInChunks;
      }
   }
}

int32_t VerifyAgainstCoreParameters(ACF_Process_PortInfo* lpPortInfo,
                                    ACF_Process_PortInfo_APU* lpPortInfoApu,
                                    int32_t lFlag1D,
                                    int32_t lNumIterations,
                                    int32_t lTileWidthInChunks,
                                    int32_t lLastTileWidthInChunks)
{
   int32_t lRetVal = 0;
   int32_t lNumIterations_tmp = 0;
   int32_t lTileWidthInChunks_tmp = 0;
   int32_t lLastTileWidthInChunks_tmp = 0;

   ACF_DataDesc* lpDD = &lpPortInfo->mDataDesc;

   if (lpPortInfoApu->IsCmem() && lpPortInfo->IsNonStatic())
   {
      if (lpPortInfo->IsDirect())
      {
         if (lFlag1D) //1D case (i.e. 1D array of chunks)
         {
            int32_t lNumChunks = (lpDD->RetWidth() + lpPortInfo->mChunkWidth - 1)/lpPortInfo->mChunkWidth;
            lNumIterations_tmp = (lNumChunks + lTileWidthInChunks - 1)/lTileWidthInChunks;
            lTileWidthInChunks_tmp = lTileWidthInChunks;
            lLastTileWidthInChunks_tmp = ((lNumChunks % lTileWidthInChunks)!= 0) ? (lNumChunks % lTileWidthInChunks) : lTileWidthInChunks;
         }
         else //2D case
         {
            lNumIterations_tmp = (lpDD->RetHeight() + lpPortInfo->mChunkHeight - 1)/lpPortInfo->mChunkHeight;
            lTileWidthInChunks_tmp = (lpDD->RetWidth() + lpPortInfo->mChunkWidth - 1)/lpPortInfo->mChunkWidth;
            lLastTileWidthInChunks_tmp = lTileWidthInChunks_tmp;
         }
      }
      else if (lpPortInfo->IsIndirect())
      {
         if (lFlag1D) //1D case (i.e. 1D list of chunks)
         {
            int32_t lNumChunks = lpPortInfo->mOffsetArray.RetWidth();
            lNumIterations_tmp = (lNumChunks + lTileWidthInChunks - 1)/lTileWidthInChunks;
            lTileWidthInChunks_tmp = lTileWidthInChunks;
            lLastTileWidthInChunks_tmp = ((lNumChunks % lTileWidthInChunks)!= 0) ? (lNumChunks % lTileWidthInChunks) : lTileWidthInChunks;
         }
         else //2D case
         {
            lNumIterations_tmp = lpPortInfo->mOffsetArray.RetHeight();
            lTileWidthInChunks_tmp = lpPortInfo->mOffsetArray.RetWidth();
            lLastTileWidthInChunks_tmp = lTileWidthInChunks_tmp;
         }

         //see cloud-616 for an explanation of why this check is necessary
         int32_t lStreamLineSize = lTileWidthInChunks_tmp*lpPortInfo->mChunkWidth*RetE0WidthInBytes(&lpPortInfo->mE0)*lpPortInfo->mE0.y*lpPortInfo->mChunkHeight;
         if (lStreamLineSize > ((1<<16)-1))
         {
            lRetVal = 1;
            printf ("GenApuProgramParams() -> combination of indirect input chunk size of %dx%d and tile width of %d exceeds HW limitations\n",
                    lpPortInfo->mChunkWidth, lpPortInfo->mChunkHeight, lTileWidthInChunks_tmp);
            return lRetVal;
         }
      }

      //ERROR CHECK
      if (lNumIterations_tmp != lNumIterations)
      {
         printf("GenApuProgramParams() -> number of iterations (%d) for input/output associated with port '%s' is inconsistent with the number of iterations for other inputs/outputs (%d)\n",
                lNumIterations_tmp, lpPortInfo->mPortIdentifier.c_str(), lNumIterations);
         lRetVal = 1;
      }

      if (lTileWidthInChunks_tmp != lTileWidthInChunks)
      {
         printf("GenApuProgramParams() -> tile width in chunks (%d) for input/output associated with port '%s' is inconsistent with the tile width in chunks for other inputs/outputs (%d)\n",
                lTileWidthInChunks_tmp, lpPortInfo->mPortIdentifier.c_str(), lTileWidthInChunks);
         lRetVal = 1;
      }

      if (lLastTileWidthInChunks_tmp != lLastTileWidthInChunks)
      {
          printf("GenApuProgramParams() -> tile width in chunks (%d) for input/output associated with port '%s' is inconsistent with the last tile width in chunks for other inputs/outputs (%d)\n",
                lLastTileWidthInChunks_tmp, lpPortInfo->mPortIdentifier.c_str(), lLastTileWidthInChunks);
          lRetVal = 1;
      }
   }
   else if (lpPortInfoApu->IsCmem() && lpPortInfo->IsStatic())
   {
      if (lpPortInfo->IsDirect())
      {
         lTileWidthInChunks_tmp = (lpDD->RetWidth() + lpPortInfo->mChunkWidth - 1)/lpPortInfo->mChunkWidth;

         if (lpDD->RetHeight() != lpPortInfo->mChunkHeight)
         {
            printf("GenApuProgramParams() -> height of the buffer connected to static vector port '%s' is %d but it is expected to be %d\n",
                   lpPortInfo->mPortIdentifier.c_str(), lpDD->RetHeight(), lpPortInfo->mChunkHeight);
            lRetVal = 1;
         }
      }
      else if (lpPortInfo->IsIndirect())
      {
         lTileWidthInChunks_tmp = lpPortInfo->mOffsetArray.RetWidth();

         if (lpPortInfo->mOffsetArray.RetHeight() != 1)
         {
            printf("GenApuProgramParams() -> height of the offset array associated with indirect static vector port '%s' is %d but it is expected to be 1\n",
                   lpPortInfo->mPortIdentifier.c_str(), lpPortInfo->mOffsetArray.RetHeight());
            lRetVal = 1;
         }
      }

      //ERROR CHECK
      if (lTileWidthInChunks_tmp != lTileWidthInChunks)
      {
         printf("GenApuProgramParams() -> tile width in chunks (%d) for static vector input/output associated with port '%s' is inconsistent with the tile width in chunks for other inputs/outputs (%d)\n",
                lTileWidthInChunks_tmp, lpPortInfo->mPortIdentifier.c_str(), lTileWidthInChunks);
         lRetVal = 1;
      }

      if (lTileWidthInChunks_tmp != lLastTileWidthInChunks)
      {
         printf("GenApuProgramParams() -> tile width in chunks (%d) for static vector input/output associated with port '%s' is inconsistent with the last tile width in chunks for other inputs/outputs (%d)\n",
                lTileWidthInChunks_tmp, lpPortInfo->mPortIdentifier.c_str(), lLastTileWidthInChunks);
         lRetVal = 1;
      }
   }
   else if (lpPortInfoApu->IsDmem() && lpPortInfo->IsNonStatic())
   {
      if (lFlag1D) //1D case
      {
         lNumIterations_tmp = (lpDD->RetWidth() + lpPortInfo->mChunkWidth - 1)/lpPortInfo->mChunkWidth;
      }
      else //2D case
      {
         lNumIterations_tmp = (lpDD->RetHeight() + lpPortInfo->mChunkHeight - 1)/lpPortInfo->mChunkHeight;

         if (lpDD->RetWidth() != lpPortInfo->mChunkWidth)
         {
            printf("GenApuProgramParams() -> width of the buffer connected to scalar port '%s' is %d but it is expected to be %d\n",
                   lpPortInfo->mPortIdentifier.c_str(), lpDD->RetWidth(), lpPortInfo->mChunkWidth);
            lRetVal = 1;
         }
      }

      //ERROR CHECK
      if (lNumIterations_tmp != lNumIterations)
      {
         printf("GenApuProgramParams() -> number of iterations (%d) for scalar input/output associated with port '%s' is inconsistent with the number of iterations for other inputs/outputs (%d)\n",
                lNumIterations_tmp, lpPortInfo->mPortIdentifier.c_str(), lNumIterations);
         lRetVal = 1;
      }
   }
   else if (lpPortInfoApu->IsDmem() && lpPortInfo->IsStatic())
   {
      //ERROR CHECK
      if (lpDD->RetHeight() != lpPortInfo->mChunkHeight || lpDD->RetWidth() != lpPortInfo->mChunkWidth)
      {
         printf("GenApuProgramParams() -> size of the buffer connected to static scalar port '%s' is %dx%d but it is expected to be %dx%d\n",
                lpPortInfo->mPortIdentifier.c_str(), lpDD->RetWidth(), lpDD->RetHeight(), lpPortInfo->mChunkWidth, lpPortInfo->mChunkHeight);
         lRetVal = 1;
      }
   }

   return lRetVal;
}

int32_t GenApuProgramParams(std::vector<ACF_Process_PortInfo> &lPortInfoVec,
                            std::vector<ACF_Process_PortInfo_APU> &lPortInfoApuVec,
                            ParamIoInfo& lParamIoInfo,
                            int32_t lRoiInfoL, int32_t lRoiInfoR, int32_t lRoiInfoT, int32_t lRoiInfoB,
                            int32_t lFlag1D,
                            int32_t lApuArrayWidth,
                            int32_t* lpParamList,
                            int32_t* lpParamListSize,
                            acf_scenario* lpScenario,
                            int32_t lSkipPortConsistencyCheck)
{
   int32_t lRetVal = 0;
   int32_t lErrorState = 0;

   //make sure all process IOs have been configured
   for (int32_t i=0; i<(int32_t)lPortInfoVec.size(); i++)
   {
      ACF_Process_PortInfo* lpPortInfo = &lPortInfoVec[i];
      if (0 == lpPortInfo->mConfiguredFlag)
      {
         printf("GenApuProgramParams() -> port '%s' has not been successfully connected\n", lpPortInfo->mPortIdentifier.c_str());
         lErrorState = 1;
      }
   }

   if (lErrorState != 0)
      return lErrorState; //<<<<<<<<<<

   //inputs
   int32_t lNumNonstaticIndirectCmemInputs = 0;
   int32_t lNumNonstaticCmemInputs         = 0;
   int32_t lNumNonstaticDmemInputs         = 0;
   int32_t lNumStaticCmemInputs            = 0;
   int32_t lNumStaticDmemInputs            = 0;
   //outputs
   int32_t lNumNonstaticCmemOutputs        = 0;
   int32_t lNumNonstaticDmemOutputs        = 0;
   int32_t lNumStaticOutputs               = 0;
   int32_t lNumFifoOutputs                 = 0;
   //global stuff
   int32_t lNumInputs                      = 0;
   int32_t lNumOutputs                     = 0;

   for (int32_t i=0; i<(int32_t)lPortInfoVec.size(); i++)
   {
      ACF_Process_PortInfo* lpPortInfo = &lPortInfoVec[i];
      ACF_Process_PortInfo_APU* lpPortInfoApu = &lPortInfoApuVec[i];

      if (lpPortInfo->IsInput() && lpPortInfo->IsNonStatic() && lpPortInfoApu->IsCmem() && lpPortInfo->IsIndirect()) //indirect nonstatic cmem input
         lNumNonstaticIndirectCmemInputs ++;
      if (lpPortInfo->IsInput() && lpPortInfo->IsNonStatic() && lpPortInfoApu->IsCmem() && lpPortInfo->IsDirect()) //nonstatic cmem input
         lNumNonstaticCmemInputs ++;
      if (lpPortInfo->IsInput() && lpPortInfo->IsNonStatic() && lpPortInfoApu->IsDmem() && lpPortInfo->IsDirect()) //nonstatic dmem input
         lNumNonstaticDmemInputs ++;
      if (lpPortInfo->IsInput() && lpPortInfo->IsStatic() && lpPortInfoApu->IsCmem()&& lpPortInfo->IsDirect()) //static input
         lNumStaticCmemInputs ++;
      if (lpPortInfo->IsInput() && lpPortInfo->IsStatic() && lpPortInfoApu->IsDmem()&& lpPortInfo->IsDirect()) //static input
         lNumStaticDmemInputs ++;
      if (lpPortInfo->IsOutput() && lpPortInfo->IsNonStatic() && lpPortInfo->IsReg() && lpPortInfoApu->IsCmem()) //nonstatic cmem output
         lNumNonstaticCmemOutputs ++;
      if (lpPortInfo->IsOutput() && lpPortInfo->IsNonStatic() && lpPortInfo->IsReg()&& lpPortInfoApu->IsDmem()) //nonstatic dmem output
         lNumNonstaticDmemOutputs ++;
      if (lpPortInfo->IsOutput() && lpPortInfo->IsStatic() && lpPortInfo->IsReg()) //static output
         lNumStaticOutputs ++;
      if (lpPortInfo->IsOutput() && lpPortInfo->IsFifo()) //fifo output
         lNumFifoOutputs ++;

      if (lpPortInfo->IsInput())
         lNumInputs ++;
      if (lpPortInfo->IsOutput())
         lNumOutputs ++;
   }

   //parameters sent to program or used to generate other parameters
   int32_t lNumInputIterations = 0;
   int32_t lNumOutputIterations = 0;
   int32_t lInputTileWidthInChunks = 0;
   int32_t lLastInputTileWidthInChunks = 0;  //in 1D case the size of the last tile is likely to be different than the previous ones
   int32_t lOutputTileWidthInChunks = 0;
   int32_t lLastOutputTileWidthInChunks = 0; //in 1D case the size of the last tile is likely to be different than the previous ones
   int32_t lStartCuAdjForRoi = 0;
   int32_t lOutputSkip = 0;
   int32_t lIOWidthInChunks1D = 0;

   //******************************************************************************************
   //NUMBER OF CORE PROCESSING ITERATIONS (derived from the first non-static input encountered)
   //******************************************************************************************

   if (lNumNonstaticCmemInputs || lNumNonstaticIndirectCmemInputs || lNumNonstaticDmemInputs)
   {
      for (int32_t i=0; i<(int32_t)lPortInfoVec.size(); i++)
      {
         ACF_Process_PortInfo* lpPortInfo = &lPortInfoVec[i];
         ACF_Process_PortInfo_APU* lpPortInfoApu = &lPortInfoApuVec[i];

         if (lpPortInfo->IsInput() && lpPortInfo->IsNonStatic())
         {
            CalcCoreParameters_NumIterations(lpPortInfo,
                                             lpPortInfoApu,
                                             lRoiInfoT,
                                             lRoiInfoB,
                                             lApuArrayWidth,
                                             lFlag1D,
                                             lNumInputIterations,
                                             lNumOutputIterations);

            //TODO: check values of lNumInputIterations and lNumOutputIterations (should be non-zero)

            break;
         }
      }
   }
   else //all inputs are static
   {
      //set number of iterations to 1 for degenerate case of all static i/o (i.e. single iteration)
      lNumInputIterations = 1;
      lNumOutputIterations = 1;
   }

   //***********************************************************************
   //CMEM TILE SIZE CALCULATIONS (derived from first cmem input encountered)
   //***********************************************************************

   if (lNumNonstaticCmemInputs || lNumNonstaticIndirectCmemInputs || lNumStaticCmemInputs)
   {
      for (int32_t i=0; i<(int32_t)lPortInfoVec.size(); i++)
      {
         ACF_Process_PortInfo* lpPortInfo = &lPortInfoVec[i];
         ACF_Process_PortInfo_APU* lpPortInfoApu = &lPortInfoApuVec[i];

         if (lpPortInfo->IsInput() && lpPortInfoApu->IsCmem())
         {
            CalcCoreParameters_TileInfo(lpPortInfo,
                                        lpPortInfoApu,
                                        lRoiInfoL,
                                        lRoiInfoR,
                                        lRoiInfoT,
                                        lApuArrayWidth,
                                        lFlag1D,
                                        lInputTileWidthInChunks,
                                        lLastInputTileWidthInChunks,
                                        lOutputTileWidthInChunks,
                                        lLastOutputTileWidthInChunks,
                                        lStartCuAdjForRoi,
                                        lOutputSkip,
                                        lIOWidthInChunks1D);

            if (lInputTileWidthInChunks > lApuArrayWidth && (!lSkipPortConsistencyCheck))
            {
               printf("GenApuProgramParams() -> the input associated with port '%s' is too wide (%d chunks) to fit into the CU array (%d CUs)\n",
                      lpPortInfo->mPortIdentifier.c_str(), lInputTileWidthInChunks, lApuArrayWidth);
               lErrorState = 1;
            }

            //TODO: check values of lInputTileWidthInChunks, lLastInputTileWidthInChunks, lOutputTileWidthInChunks, lLastOutputTileWidthInChunks (should be non-zero)

            break;
         }
      }
   }

   if (lErrorState != 0)
     return lErrorState; //<<<<<<<<<<

   //*******************************************************************************************
   //verify consistency of all other inputs and outputs against core parameters calculated above
   //*******************************************************************************************

   for (int32_t i=0; i<(int32_t)lPortInfoVec.size(); i++)
   {
      ACF_Process_PortInfo* lpPortInfo = &lPortInfoVec[i];
      ACF_Process_PortInfo_APU* lpPortInfoApu = &lPortInfoApuVec[i];

      if (lpPortInfo->IsReg() && (!lSkipPortConsistencyCheck))
      {
         if (VerifyAgainstCoreParameters(lpPortInfo,
                                         lpPortInfoApu,
                                         lFlag1D,
                                         lNumOutputIterations,
                                         lOutputTileWidthInChunks,
                                         lLastOutputTileWidthInChunks))
         {
            lErrorState = 1;
         }
      }
   }

   if (lErrorState != 0)
      return lErrorState; //<<<<<<<<<<

   //*******************************************************************************
   //initialize the shared 'acf_io_desc' memory region
   //*******************************************************************************

   const int32_t lIoDescOffset = 16 + ((sizeof(acf_res_info)+3)>>2); //remember to sync with ACF_Process_Desc_APU and RTLSIM!!
   const int32_t lScenarioDataSizeInWords = 1 + ((lpScenario->scenarioBufferDataSizeInBytes+3)>>2) +
                                                ((lpScenario->scenarioKernelDataSizeInBytes+3)>>2);

   int32_t lTempSize = lIoDescOffset +
                       (lNumNonstaticIndirectCmemInputs*(sizeof(acf_io_mce_desc)>>2)) +
                       ((lNumNonstaticCmemInputs                     +
                         lNumNonstaticDmemInputs                     +
                         lNumStaticCmemInputs                        +
                         lNumStaticDmemInputs                        +
                         lNumNonstaticCmemOutputs                    +
                         lNumNonstaticDmemOutputs                    +
                         lNumStaticOutputs                           +
                         lNumFifoOutputs)*(sizeof(acf_io_desc)>>2))  +
                         lScenarioDataSizeInWords;

   //make sure parameter list doesn't overflow allotted size (*lpParamListSize initialized with 'max')
   if (lTempSize <= *lpParamListSize)
   {
      *lpParamListSize = lTempSize;
   }
   else
   {
      printf("GenApuProgramParams() -> Size of parameter list exceeded maximum\n");
      lErrorState = 1;
      return lErrorState; //<<<<<<<<<<
   }

   //******************************************************************************************************
   //the order of these is IMPORTANT; host packing order must match with the apu program's unpacking order
   //******************************************************************************************************

   int32_t* lpTemp = lpParamList + lIoDescOffset;

   //IO info within the param list must be identified (needed for launcher, mostly for ISS)
   lParamIoInfo.mNumMceIos = lNumNonstaticIndirectCmemInputs;
   lParamIoInfo.mNumInIos = lNumNonstaticCmemInputs + lNumNonstaticDmemInputs + lNumStaticCmemInputs + lNumStaticDmemInputs;
   lParamIoInfo.mNumOutIos = lNumNonstaticCmemOutputs + lNumNonstaticDmemOutputs + lNumStaticOutputs + lNumFifoOutputs;
   lParamIoInfo.mpMceIos = (acf_io_mce_desc*)lpTemp;
   lParamIoInfo.mpInIos = (acf_io_desc*)((uintptr_t)lParamIoInfo.mpMceIos + (lParamIoInfo.mNumMceIos*sizeof(acf_io_mce_desc)));
   lParamIoInfo.mpOutIos = (acf_io_desc*)((uintptr_t)lParamIoInfo.mpInIos + (lParamIoInfo.mNumInIos*sizeof(acf_io_desc)));

   acf_io_mce_desc* lpIoDesc_NonstaticIndirectCmemInputs = (acf_io_mce_desc*)lpTemp;
   lpTemp += lNumNonstaticIndirectCmemInputs*sizeof(acf_io_mce_desc)>>2;

   acf_io_desc* lpIoDesc_NonstaticCmemInputs = (acf_io_desc*)lpTemp;
   lpTemp += lNumNonstaticCmemInputs*sizeof(acf_io_desc)>>2;

   acf_io_desc* lpIoDesc_NonstaticDmemInputs = (acf_io_desc*)lpTemp;
   lpTemp += lNumNonstaticDmemInputs*sizeof(acf_io_desc)>>2;

   acf_io_desc* lpIoDesc_StaticInputs  = (acf_io_desc*)lpTemp;
   lpTemp += (lNumStaticCmemInputs + lNumStaticDmemInputs)*sizeof(acf_io_desc)>>2;

   acf_io_desc* lpIoDesc_NonstaticCmemOutputs = (acf_io_desc*)lpTemp;
   lpTemp += lNumNonstaticCmemOutputs*sizeof(acf_io_desc)>>2;

   acf_io_desc* lpIoDesc_NonstaticDmemOutputs = (acf_io_desc*)lpTemp;
   lpTemp += lNumNonstaticDmemOutputs*sizeof(acf_io_desc)>>2;

   acf_io_desc* lpIoDesc_StaticOutputs = (acf_io_desc*)lpTemp;
   lpTemp += lNumStaticOutputs*sizeof(acf_io_desc)>>2;

   acf_io_desc* lpIoDesc_FifoOutputs = (acf_io_desc*)lpTemp;
   lpTemp += lNumFifoOutputs*sizeof(acf_io_desc)>>2;

   //scenario
   int32_t* lpScenarioIterAdjust = (int32_t*)lpTemp;
   *lpScenarioIterAdjust = lpScenario->iterAdjustment;
   lpTemp += 1;
   int32_t* lpScenarioBufferData = (int32_t*)lpTemp;
   memcpy((void*)lpScenarioBufferData, (void*)(lpScenario->pBufferData), lpScenario->scenarioBufferDataSizeInBytes);
   lpTemp += (lpScenario->scenarioBufferDataSizeInBytes+3)>>2;
   int32_t* lpScenarioKernelData = (int32_t*)lpTemp;
   memcpy((void*)lpScenarioKernelData, (void*)(lpScenario->pKernelData), lpScenario->scenarioKernelDataSizeInBytes);
   lpTemp += (lpScenario->scenarioKernelDataSizeInBytes+3)>>2;

   int32_t lIndex_NonstaticIndirectCmemInputs = 0;
   int32_t lIndex_NonstaticCmemInputs         = 0;
   int32_t lIndex_NonstaticDmemInputs         = 0;
   int32_t lIndex_StaticInputs                = 0;
   int32_t lIndex_NonstaticCmemOutputs        = 0;
   int32_t lIndex_NonstaticDmemOutputs        = 0;
   int32_t lIndex_StaticOutputs               = 0;
   int32_t lIndex_FifoOutputs                 = 0;

#if (1 == DEBUG_IODUMP)
   //DUMP ALL inputs for sim/debugging (will be 'packed' into a single region of memory to simplify things)
   uint8_t* lTmpBuffer = new uint8_t[10*(1024*1000)]; //make it 10 megs for now
   memset((void*)lTmpBuffer, 0, 10*(1024*1000));
   int32_t lOffset = 0; //running buffer offset
#endif

   //initialize NonstaticIndirectCmemInput (i.e. MCE) IO descriptors
   if (lNumNonstaticIndirectCmemInputs)
   {
      for (int32_t i=0; i<(int32_t)lPortInfoVec.size(); i++)
      {
         int32_t* lpIndex = &lIndex_NonstaticIndirectCmemInputs;
         acf_io_mce_desc* lpIoDesc = lpIoDesc_NonstaticIndirectCmemInputs;

         ACF_Process_PortInfo* lpPortInfo = &lPortInfoVec[i];
         ACF_Process_PortInfo_APU* lpPortInfoApu = &lPortInfoApuVec[i];

         if (lpPortInfo->IsInput() && lpPortInfo->IsNonStatic() && lpPortInfo->IsIndirect() && lpPortInfoApu->IsCmem()) //non-static indirect cmem input
         {
            lpIoDesc[*lpIndex].offsetArrayWidth  = lpPortInfo->mOffsetArray.RetWidth();
            lpIoDesc[*lpIndex].offsetArrayHeight = lpPortInfo->mOffsetArray.RetHeight();
            if (1 == lFlag1D) //1D
               lpIoDesc[*lpIndex].tileOffset = lInputTileWidthInChunks*4;
            else //2D
               lpIoDesc[*lpIndex].tileOffset = lpPortInfo->mOffsetArray.RetSpan();
            lpIoDesc[*lpIndex].srcDataSpan       = lpPortInfo->mDataDesc.RetSpan();
            lpIoDesc[*lpIndex].physBaseAddr     = (uintptr_t)lpPortInfo->mDataDesc.RetDataPtrPhys();
            lpIoDesc[*lpIndex].physPtrArrayAddr = (uintptr_t)lpPortInfo->mOffsetArray.RetDataPtrPhys();
            lpIoDesc[*lpIndex].srcSizeInBytes = lpPortInfo->mDataDesc.RetHeightSpan()*lpPortInfo->mDataDesc.RetHeight()*lpPortInfo->mDataDesc.RetElementDimY();
            (*lpIndex) ++;
         }
      }
   }

   //initialize all other IO descriptors
   for (int32_t i=0; i<(int32_t)lPortInfoVec.size(); i++)
   {
      ACF_Process_PortInfo* lpPortInfo = &lPortInfoVec[i];
      ACF_Process_PortInfo_APU* lpPortInfoApu = &lPortInfoApuVec[i];

      int32_t* lpIndex = 0;
      acf_io_desc* lpIoDesc = 0;

      if (lpPortInfo->IsInput() && lpPortInfo->IsNonStatic() && lpPortInfoApu->IsCmem() && lpPortInfo->IsDirect()) //nonstatic cmem input
      {
         lpIndex = &lIndex_NonstaticCmemInputs;
         lpIoDesc = lpIoDesc_NonstaticCmemInputs;
      }
      else if (lpPortInfo->IsInput() && lpPortInfo->IsNonStatic() && lpPortInfoApu->IsDmem() && lpPortInfo->IsDirect()) //nonstatic dmem input
      {
         lpIndex = &lIndex_NonstaticDmemInputs;
         lpIoDesc = lpIoDesc_NonstaticDmemInputs;
      }
      else if (lpPortInfo->IsInput() && lpPortInfo->IsStatic() && lpPortInfo->IsDirect()) //static input
      {
         lpIndex = &lIndex_StaticInputs;
         lpIoDesc = lpIoDesc_StaticInputs;
      }
      else if (lpPortInfo->IsOutput() && lpPortInfo->IsNonStatic() && lpPortInfo->IsReg() && lpPortInfoApu->IsCmem()) //nonstatic cmem output
      {
         lpIndex = &lIndex_NonstaticCmemOutputs;
         lpIoDesc = lpIoDesc_NonstaticCmemOutputs;
      }
      else if (lpPortInfo->IsOutput() && lpPortInfo->IsNonStatic() && lpPortInfo->IsReg() && lpPortInfoApu->IsDmem()) //nonstatic dmem output
      {
         lpIndex = &lIndex_NonstaticDmemOutputs;
         lpIoDesc = lpIoDesc_NonstaticDmemOutputs;
      }
      else if (lpPortInfo->IsOutput() && lpPortInfo->IsStatic() && lpPortInfo->IsReg()) //static output
      {
         lpIndex = &lIndex_StaticOutputs;
         lpIoDesc = lpIoDesc_StaticOutputs;
      }
      else if (lpPortInfo->IsOutput() && lpPortInfo->IsFifo())
      {
         lpIndex = &lIndex_FifoOutputs;
         lpIoDesc = lpIoDesc_FifoOutputs;
      }

      if (lpIoDesc)
      {
         ACF_DataDesc* lpDD = &lpPortInfo->mDataDesc;

         int32_t lChannel  = lpDD->RetChannel();
         int32_t lWidth    = lpDD->RetWidth();
         int32_t lHeight   = lpDD->RetHeight();
         int32_t lBatch    = lpDD->RetBatch();

         int32_t lChannelSpan  = lpDD->RetChannelSpan();
         int32_t lWidthSpan    = lpDD->RetWidthSpan();
         int32_t lHeightSpan   = lpDD->RetHeightSpan();
         int32_t lBatchSpan    = lpDD->RetBatchSpan();

         uint64_t lPhysAddr = (uintptr_t)lpDD->RetDataPtrPhys();
         int32_t lPhysAddrPullBack = 0;

         //pull back the physical pointer so the actual data transfer will include the padding
         if (1 == lpPortInfo->mVerDepOverlapFlag)
            lPhysAddrPullBack += (lpDD->RetSpan()*lpDD->RetElementDimY()*lpScenario->pBufferData[lpPortInfo->mLmIndex].padding.n);

         int32_t lRoiL = 0;
         int32_t lRoiR = 0;
         int32_t lRoiT = 0;
         int32_t lRoiB = 0;
         if (lpIndex == &lIndex_NonstaticCmemInputs) //if non-static direct cmem input must adjust input size based on ROI info
         {
            //adjust for ROI (it is currently assumed that ROIs are nicely located and requirements
            //for additional data are met by transferring the fewest number of FULL CHUNKS/TILES)
            lRoiL = ((lRoiInfoL + lpPortInfo->mChunkWidth - 1)/lpPortInfo->mChunkWidth)*lpPortInfo->mChunkWidth;
            lRoiR = ((lRoiInfoR + lpPortInfo->mChunkWidth - 1)/lpPortInfo->mChunkWidth)*lpPortInfo->mChunkWidth;
            lRoiT = ((lRoiInfoT + lpPortInfo->mChunkHeight - 1)/lpPortInfo->mChunkHeight)*lpPortInfo->mChunkHeight;
            lRoiB = ((lRoiInfoB + lpPortInfo->mChunkHeight - 1)/lpPortInfo->mChunkHeight)*lpPortInfo->mChunkHeight;

            lWidth  += (lRoiL + lRoiR);
            lHeight += (lRoiT + lRoiB);
            lPhysAddrPullBack += lRoiT*lpDD->RetElementDimY()*lHeightSpan;
            lPhysAddrPullBack += RetDataTypeSizeInBytes(lpDD->RetElementDataType())*lpDD->RetElementDimX()*lRoiL;
         }

         //this value is capturing the total footprint of the IO region in memory (used primarily for ISS since it needs to
         //copy all relevant data between ARM memory and ISS memory)
         int32_t lTotalRegionSizeInBytes = lHeightSpan*lpDD->RetElementDimY()*lHeight;
         if (1 == lpPortInfo->mVerDepOverlapFlag)
         {
            int32_t lPadSize = lpScenario->pBufferData[lpPortInfo->mLmIndex].padding.n + lpScenario->pBufferData[lpPortInfo->mLmIndex].padding.s;
            lTotalRegionSizeInBytes += lHeightSpan * lpDD->RetElementDimY() * lPadSize;
         }

         lPhysAddr -= lPhysAddrPullBack;

#if (1 == DEBUG_IODUMP)
         static int32_t lOverridePhys = 0;
         uint32_t lSizeInBytes = lpDD->RetSpan()*lpDD->RetHeight();
         uint32_t lAddr        = (uint32_t)lpDD->RetDataPtr();
         lAddr -= lRoiT*lpDD->RetElementDimY()*lHeightSpan;
         lAddr -= RetDataTypeSizeInBytes(lpDD->RetElementDataType())*lpDD->RetElementDimX()*lRoiL;
         if (lpPortInfo->IsInput())
               memcpy((void*)(&lTmpBuffer[lOffset]), (void*)lAddr, lSizeInBytes);
         if (lOverridePhys)
            lPhysAddr = gExtMemBaseAddr + lOffset; //***OVERRIDE 'real' physical with sim friendly physical that will match with dumped IO
         printf("Offset for %15s = %7d (size = %7d bytes)\n",lpPortInfo->mPortIdentifier.c_str(), lOffset, lSizeInBytes);
         lOffset += (lSizeInBytes + 15)&0xFFFFFFF0; //ensure each buffer is 128-bit aligned
#endif

         lpIoDesc[*lpIndex].nd_size.channel = lChannel;
         lpIoDesc[*lpIndex].nd_size.width   = lWidth;
         lpIoDesc[*lpIndex].nd_size.height  = lHeight;
         lpIoDesc[*lpIndex].nd_size.batch   = lBatch;
         lpIoDesc[*lpIndex].nd_span.channel = lChannelSpan;
         lpIoDesc[*lpIndex].nd_span.width   = lWidthSpan;
         lpIoDesc[*lpIndex].nd_span.height  = lHeightSpan;
         lpIoDesc[*lpIndex].nd_span.batch   = lBatchSpan;

         lpIoDesc[*lpIndex].e0span      = lHeightSpan*lpDD->RetElementDimY();
         lpIoDesc[*lpIndex].physAddr    = lPhysAddr;
         lpIoDesc[*lpIndex].sizeInBytes = lTotalRegionSizeInBytes;

         if (1 == lFlag1D) //1D
         {
            int32_t lNumChunks = 1;
            if (lpPortInfoApu->IsCmem())
               lNumChunks = lInputTileWidthInChunks;
            lpIoDesc[*lpIndex].tileOffset = lpPortInfo->mChunkWidth*RetE0SizeInBytes(&lpPortInfo->mE0)*lNumChunks;
         }
         else //2D (assume tileOffset only needed by 1D&2D cases but not tensor processing, for which all memory are allocated as static and manually managed)
         {
            lpIoDesc[*lpIndex].tileOffset = lpPortInfo->mChunkHeight*lHeightSpan*lpDD->RetElementDimY();
         }

         (*lpIndex) ++;
      }
   }

#if (1 == DEBUG_IODUMP)
   FILE* pInputDumpFile = fopen("c:\\inputdump.bin", "wb");
   fwrite((void*)lTmpBuffer, 1, lOffset, pInputDumpFile);
   fclose(pInputDumpFile);
   delete lTmpBuffer;
#endif

   lpParamList[0] = lNumInputIterations;
   lpParamList[1] = lInputTileWidthInChunks;
   lpParamList[2] = lStartCuAdjForRoi;
   lpParamList[3] = lOutputTileWidthInChunks;
   lpParamList[4] = lNumOutputIterations;
   lpParamList[5] = lOutputSkip;
   lpParamList[6] = lLastInputTileWidthInChunks;
   lpParamList[7] = lLastOutputTileWidthInChunks;

   if (lErrorState)
      lRetVal = 1;

   return lRetVal;
}
