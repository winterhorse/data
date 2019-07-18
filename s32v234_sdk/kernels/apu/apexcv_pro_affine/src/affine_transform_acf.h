/*****************************************************************************
* 
* NXP Confidential Proprietary
*
* Copyright (c) 2014-2016 Freescale Semiconductor
* Copyright 2017-2018 NXP 
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
*  \file affine_transform_apu.cpp
*  \brief ACF Affine Transform Wrapper.
***********************************************************************************/
/*!*********************************************************************************
*  @file
*  @brief ACF metadata and wrapper function for the \ref secAffineTransform "affine transformation".
***********************************************************************************/

#ifndef ACFAFFINETRANSFORMWRAP_H
#define ACFAFFINETRANSFORMWRAP_H

#ifdef ACF_KERNEL_METADATA
#include "common_stringify_macros.h"
#define AFFINE_BILINEAR_INTERPOLATE_K             affine_bilinear_interpolate
#define AFFINE_BILINEAR_INTERPOLATE_KN            XSTR(AFFINE_BILINEAR_INTERPOLATE_K)
#define INPUT                           "INPUT"
#define MATRIX                          "MATRIX"
#define IMAGE_WIDTH                     "IMAGE_WIDTH"
#define IMAGE_HEIGHT                    "IMAGE_HEIGHT"
#define OUTPUT                          "OUTPUT"

extKernelInfoDecl(AFFINE_BILINEAR_INTERPOLATE_K);

#endif // ACF_KERNEL_METADATA

#endif /* ACFAFFINETRANSFORMWRAP_H */
