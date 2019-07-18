/*****************************************************************************
* 
* NXP Confidential Proprietary
*
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
*  @file
*  @brief ACF metadata and wrapper function for the \ref secHarrisCorner "harris corner".
***********************************************************************************/
#ifndef APUFLTBOXGENERICACF_H
#define APUFLTBOXGENERICACF_H

#include "common_stringify_macros.h"
#define FLT_BOX_GENERIC_K    apu_flt_box_generic_16s
#define FLT_BOX_GENERIC_KN   XSTR( FLT_BOX_GENERIC_K)

#define HARRIS_BOX_5X5_K     harris_box_5x5_16s
#define HARRIS_BOX_5X5_KN    XSTR(HARRIS_BOX_5X5_K)


#define FLT_BOX_GENERIC_K_IN  "INPUT_0"
#define FLT_BOX_GENERIC_K_OUT "OUTPUT_0"

#define HARRIS_BOX_K_IN       "INPUT_0"
#define HARRIS_BOX_K_OUT      "OUTPUT_0"

#ifdef APEX2_EMULATE

#include "acf_kernel.hpp"
using namespace APEX2;

void FLT_BOX_GENERIC_K(kernel_io_desc in0, kernel_io_desc out0);
void HARRIS_BOX_5X5_K(kernel_io_desc in0, kernel_io_desc out0);
#endif //APEX2_EMULATE

#if (defined(ACF_KERNEL_METADATA) || (!defined(__chess__)))
extKernelInfoDecl(FLT_BOX_GENERIC_K);
extKernelInfoDecl(HARRIS_BOX_5X5_K);
#endif /* ACF_KERNEL_METADATA */

#endif /* APUFLTBOXGENERICACF_H */