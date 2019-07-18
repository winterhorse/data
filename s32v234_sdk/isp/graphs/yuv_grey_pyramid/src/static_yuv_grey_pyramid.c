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

/**
 * \file    static_yuv_grey_pyramid.c
 * \brief   ISP (sequencer) static configuration
 * \author  Armin Strobl
 * \author
 * \version 0.1
 * \date    12-10-2017
 * \note    initial version
 ****************************************************************************/

#include "seq_static.h"

/*****************************************************************************
* consts
*****************************************************************************/

#define IPUS1_START 1
#define IPUS2_START (IPUS1_START+3+0)
#define IPUS5_START (IPUS2_START+3+0)
#define IPUV1_START (IPUS5_START+1+0)
#define IPUS3_START (IPUV1_START+1+0)
#define IPUS6_START (IPUV1_START+2+0)
#define IPUS0_START (IPUS6_START+2+0)
#define IPUS4_START (IPUS0_START+2+0)
#define IPUS7_START (IPUS4_START+2+0)
#define IPUV0_START (IPUS7_START+2+0)

#define FDMA0_START (IPUS3_START+1+0)   // YUV
#define FDMA1_START (IPUS6_START+1+0)   // Y2
#define FDMA2_START (IPUS0_START+1+0)   // Y4
#define FDMA3_START (IPUS4_START+1+0)   // Y8
#define FDMA4_START (IPUS7_START+1+0)   // Y16
#define FDMA5_START (IPUV0_START+1+0)   // Y32

/****************************************************************************/

void StaticSequencing(void)
{
  sStaticSeq = STAT_SEQ_MIPI;

  initIPUnode(3,  IPUS1_START, 0x1,  0);    /* Expose */
  initIPUnode(4,  IPUS2_START, 0x1,  0);    /* DebayerG */
  initIPUnode(5,  IPUS5_START, 0x1,  0);    /* DebayerBR */
  initIPUnode(6,  IPUV1_START, 0x1,  0);    /* RGB2YUV */
  initIPUnode(2,  IPUS3_START, 0x1,  0);    /* ConvYUV */
  initIPUnode(7,  IPUS6_START, 0x2,  0);    /* Y2 */
  initIPUnode(8,  IPUS0_START, 0x4,  0);    /* Y4 */
  initIPUnode(9,  IPUS4_START, 0x8,  0);    /* Y8 */
  initIPUnode(10, IPUS7_START, 0x10, 0);    /* Y16 */
  initIPUnode(11, IPUV0_START, 0x20, 0);    /* Y32 */

  initFDMAnode(0, FDMA0_START, 0x1);
  initFDMAnode(1, FDMA1_START, 0x2);
  initFDMAnode(2, FDMA2_START, 0x4);
  initFDMAnode(3, FDMA3_START, 0x8);
  initFDMAnode(4, FDMA4_START, 0x10);
  initFDMAnode(5, FDMA5_START, 0x20);

} // StaticSequencing()

/* EOF */
