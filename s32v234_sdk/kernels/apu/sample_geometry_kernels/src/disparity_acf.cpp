/*****************************************************************************
*
* NXP Confidential Proprietary
*
* Copyright (c) 2013 Freescale Semiconductor;
* Copyright (c) 2017-2018 NXP
* 
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

/*!
* \file disparity_acf.cpp
* \addtogroup arithmetic
* \addtogroup addition
* \ingroup arithmetic
* @{
* \brief Element-wise addition
*/
#ifdef APEX2_EMULATE
#include "acf_kernel.hpp" // if using the ACF emulation library
using namespace APEX2;
#endif

#ifdef ACF_KERNEL_METADATA
#include "disparity_acf.h"

#include "disparity_acf.h"


/****************************************************************************/
/*!
Addition kernel metadata. Adds pixelwise two unsigned 8bit images.
Outputs 16bit unsigned addition result.

\param  ADD_KN				Define for Kernel name
\param 3					Number of ports
\param "Port ADD_KN_INA"	Define for name of first input image (unsigned 8bit)
\param "Port ADD_KN_INB"	Define for name of second input image (unsigned 8bit)
\param "Port ADD_KN_OUT"	Define for name of addition result of the two images (unsigned 16bit).
*****************************************************************************/
KERNEL_INFO  kernelInfoConcat(DISPARITY_K)
(
DISPARITY_KN,
3,
__port(__index(0),
__identifier(DISPARITY_KN_INA),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(1, 1, 1, 1),
__e0_data_type(d08u),
__e0_size(1, 1),
__ek_size(1, 1)),
__port(__index(1),
__identifier(DISPARITY_KN_INB),
__attributes(ACF_ATTR_VEC_IN),
__spatial_dep(1, 64, 1, 2),
__e0_data_type(d08u),
__e0_size(1, 1),
__ek_size(1, 1)),
__port(__index(2),
__identifier(DISPARITY_KN_OUT),
__attributes(ACF_ATTR_VEC_OUT),
__spatial_dep(0, 0, 0, 0),
//__e0_data_type(d16u),
__e0_data_type(d08u),
__e0_size(1, 1),
__ek_size(1, 1))
);

#endif //#ifdef ACF_KERNEL_METADATA

#ifdef ACF_KERNEL_IMPLEMENTATION

#include "disparity_apu.h"

void apu_disparity(kernel_io_desc in0, kernel_io_desc in1, kernel_io_desc out0)
{
	vec08u*        lIn0 = (vec08u*)in0.pMem;
	vec08u*        lIn1 = (vec08u*)in1.pMem;
	vec08u*        lOut0 = (vec08u*)out0.pMem;

	int32s inStrideW0 = in0.chunkSpan / sizeof(int08u);
	int32s inStrideW1 = in1.chunkSpan / sizeof(int08u);
	int32s outStrideW = out0.chunkSpan / sizeof(int08s);

	disparity(
		lOut0, 
		lIn0, 
		lIn1, 
		in0.chunkWidth, 
		in0.chunkHeight,
		in1.chunkWidth,
		in1.chunkHeight,
		inStrideW0, 
		inStrideW1, 
		outStrideW
		);

}

#endif //#ifdef ACF_KERNEL_IMPLEMENTATION

/*! @} */
