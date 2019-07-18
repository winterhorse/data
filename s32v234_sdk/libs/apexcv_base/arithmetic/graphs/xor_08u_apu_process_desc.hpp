/*****************************************************************************
* 
* NXP Confidential Proprietary
*
* Copyright (c) 2013-2016 Freescale Semiconductor
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
***************************************************************************
  
/*!*********************************************************************************
*  @file xor_08u_proc_desc.hpp
*  @brief Process description for bitwise xor (unsigned 8 bit)
***********************************************************************************/
#ifndef XOR08UAPUPROCESSDESC_HPP
#define XOR08UAPUPROCESSDESC_HPP

#include <acf_process_desc_apu.hpp>
#include <acf_graph.hpp>
#include "graph_templates.h"
#include "arithmetic_acf.h"

GRAPH_CLASS_DEF_2In_1Out(XOR_08u_K);

#define XOR_08U_P_ID  XOR_08U
#define XOR_08U_P_STR  XSTR(XOR_08U_P_ID)


class xor_08u_apu_process_desc : public ACF_Process_Desc_APU
{
public:
  void Create()
  {
    Initialize(mGraph, XOR_08U_P_STR);
  }

  graphClassName(XOR_08u_K) mGraph;
};

#ifdef APEX2_EMULATE
REGISTER_PROCESS_TYPE(XOR_08U_P_ID, xor_08u_apu_process_desc);
#endif


#endif /* XOR08UAPUPROCESSDESC_HPP */
