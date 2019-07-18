/*****************************************************************************
* 
* NXP Confidential Proprietary
*
* Copyright (c) 2014-2016 Freescale Semiconductor
* Copyright 2017 NXP 
* All Rights Reserved
*
******************************************************************************
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

/*==================================================================================================
Revision History:
                              Modification     Tracking
Author (core ID)              Date D/M/Y       Number     Description of Changes
---------------------------   ----------    ------------  ------------------------------------------
Adrian Grigore (nxa11567)     14/12/2016    VSDK-554      Created
---------------------------   ----------    ------------  ------------------------------------------
==================================================================================================*/
/*!*********************************************************************************
*  \file laplacian_pyramid_mid_apu_process_desc.hpp
*  \brief ACF process description for the Laplacian image pyramid creation - mid level.
***********************************************************************************/
#ifndef LAPLACIANPYRAMIDMIDAPUPROCESSDESC_HPP
#define LAPLACIANPYRAMIDMIDAPUPROCESSDESC_HPP

#include <acf_process_desc_apu.hpp>
#include "laplacian_pyramid_mid_graph.hpp"

class laplacian_pyramid_mid_apu_process_desc : public ACF_Process_Desc_APU
{
public:
   void Create()
   {
      Initialize(mGraph, "LAPLACIAN_PYRAMID_MID");
   }
   
   laplacian_pyramid_mid_graph mGraph;
};


#endif /* LAPLACIANPYRAMIDMIDAPUPROCESSDESC_HPP */
