/*****************************************************************************
*
* NXP Confidential Proprietary
*
* Copyright (c) 2014-2016 Freescale Semiconductor
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
/**
 * \file    ov10640_12bcomb_surround.c
 * \brief   ISP (sequencer) static configuration
 * \author
 * \author
 * \version 0.1
 * \date    24-08-2016
 * \note    initial version
 ****************************************************************************/

#include "seq_static.h"

/*****************************************************************************
* consts
*****************************************************************************/

#define	IPUS0_START	3
#define	IPUS1_START	4

#define	IPUV0_START	(IPUS0_START+2)
#define	IPUS2_START	(IPUV0_START+1)
#define	IPUV1_START	(IPUS2_START+1)

#define	IPUV2_START	(IPUS1_START+2)
#define	IPUS3_START	(IPUV2_START+1)
#define	IPUV3_START	(IPUS3_START+1)

#define	FDMA0_START	(IPUV1_START+1)	    // RGB0
#define	FDMA1_START	(IPUV3_START+1)	    // RGB1

/****************************************************************************/

void StaticSequencing(void)
{
  sStaticSeq = STAT_SEQ_MIPI;

  initIPUnode(2,  IPUS0_START, 0x2, 0);	/* Debayer0 */
  initIPUnode(4,  IPUS1_START, 0x2, 0);	/* Debayer1 */
  initIPUnode(3,  IPUV0_START, 0x2, 0);	/* RGB2Y0 */
  initIPUnode(6,  IPUS2_START, 0x2, 0);	/* LUT4K0 */
  initIPUnode(7,  IPUV1_START, 0x2, 0);	/* COMPRESS0 */
  initIPUnode(5,  IPUV2_START, 0x2, 0);	/* RGB2Y1 */
  initIPUnode(8,  IPUS3_START, 0x2, 0);	/* LUT4K1 */
  initIPUnode(9,  IPUV3_START, 0x2, 0);	/* COMPRESS1 */

  initFDMAnode(0, FDMA0_START, 0x2);
  initFDMAnode(1, FDMA1_START, 0x2);
} // StaticSequencing()

/* EOF */
