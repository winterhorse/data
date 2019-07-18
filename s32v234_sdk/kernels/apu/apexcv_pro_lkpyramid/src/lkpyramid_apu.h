/*****************************************************************************
* 
* NXP Confidential Proprietary
*
* Copyright (c) 2016 Freescale Semiconductor
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

#ifndef LKPYRAMIDAPU_H
#define LKPYRAMIDAPU_H

#include "lkpyramid_setup.h"

#ifdef ACF_KERNEL_IMPLEMENTATION

#include <stdint.h>

void apu_lkpyramid_templ_bilinear_Q8(
      vec08u* dst, int dstr,
      const vec08u* src, int sstr,
      const vec32s* coor_i,
      int bw, int bh,
      int shift);
      
void apu_lkpyramid_core(
      vec32s *coor_o,
      vec32s *patch_offset_o,
      vec32s *templ_offset_next_o,
      vec08u *patch, int patchstride,
      vec08u *templ, int templstride, 
      vec16s *dx, int dxstride,
      vec16s *dy, int dystride,
      vec32s *coor_i,
      vec32s *patch_offset_base,
      vec32s *templ_coor_next,
      vec08u *patchwin, int patchwinstride,
      vec16s *dtwin, int dtwinstride,
      int bw_templ, int bh_templ,
      int bw_patch, int bh_patch,
      int num_iter,
      int src_span);

#endif /* ACF_KERNEL_IMPLEMENTATION */
#endif /* LKPYRAMIDAPU_H */