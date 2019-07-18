/*****************************************************************************
* 
* NXP Confidential Proprietary
*
* Copyright 2018 NXP 
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
  
/*!*********************************************************************************
*  @file scharr_5x5_08u_proc_desc.hpp
*  @brief Process description for scharr 5x5 filter (unsigned 8 bit)
***********************************************************************************/
 
#ifndef SCHARR5X508UAPUPROCESSDESC_HPP
#define SCHARR5X508UAPUPROCESSDESC_HPP

#include <acf_process_desc_apu.hpp>
#include "scharr_5x5_08u_graph.hpp"



class scharr_5x5_08u_apu_process_desc : public ACF_Process_Desc_APU
{
public:
   void Create()
   {
      Initialize(mGraph, "SCHARR_5X5_08U");
   }
   
   scharr_5x5_08u_graph mGraph;
};
#endif /* SCHARR5X508UAPUPROCESSDESC_HPP */
