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
  
/*!*********************************************************************************
*  @file abs_08u_graph.hpp
*  @brief ACF graph for absolute difference
***********************************************************************************/
#ifndef ALLINTERPOLGRAPHREGISTRATIONS_H
#define ALLINTERPOLGRAPHREGISTRATIONS_H


#ifndef APEX2_EMULATE
#include <icp_data.h>
using namespace icp;
#include <INTERP_BILINEAR_GRAYSCALE.hpp>
#include <INTERP_LINEAR_GRAYSCALE.hpp>
#include <INTERP_BICUBIC_GRAYSCALE.hpp>

#include "graph_templates.h"
#include "interpolation_acf.h"

#else

#include "acf_lib.hpp"
using namespace APEX2;


#include "interp_bilinear_grayscale_apu_process_desc.hpp"
#include "interp_linear_grayscale_apu_process_desc.hpp"
#include "interp_bicubic_grayscale_apu_process_desc.hpp"


REGISTER_PROCESS_TYPE(INTERP_LINEAR_GRAYSCALE, interp_linear_grayscale_apu_process_desc)
REGISTER_PROCESS_TYPE(INTERP_BILINEAR_GRAYSCALE, interp_bilinear_grayscale_apu_process_desc)
REGISTER_PROCESS_TYPE(INTERP_BICUBIC_GRAYSCALE, interp_bicubic_grayscale_apu_process_desc)

#endif


#endif /* ALLINTERPOLGRAPHREGISTRATIONS_H */
