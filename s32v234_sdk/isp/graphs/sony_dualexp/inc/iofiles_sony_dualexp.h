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
 * \file    iofiles_sony_dualexp.h
 * \brief   ISP sony_y graph
 * \author  Armin Strobl
 * \author
 * \version 0.1
 * \date    12-05-2015
 * \note    inital version
 ****************************************************************************/

#ifndef	IOFILES_SONY_DUALEXP_H
#define	IOFILES_SONY_DUALEXP_H

// 0 or 1
//#define	MULTITRIGGER	0

// input image geometry
//#define	NUM_CAM_LINES	(((NUM_IN_LINES+22)*2)|1)
#define	NUM_CAM_LINES	(1550)
#define	NUM_CAM_PIXELS	(1288)
#define	NUM_CAM_STRIDE	(1288*2)
#define	NUM_CAM_FDMASTRD (1288*2 + 16)

#define	NUM_IN_LINES	(728)
#define	NUM_IN_M1	(NUM_IN_LINES-1)
#define	NUM_IN_M2	(NUM_IN_LINES-2)
#define	NUM_IN_M4	(NUM_IN_LINES-4)
#define	NUM_IN_M6	(NUM_IN_LINES-6)
#define	NUM_IN_M8	(NUM_IN_LINES-8)
#define	NUM_LINES	(NUM_IN_LINES)

// output image geometry
#define	NUM_OUT_PIXELS	(1280)
#define	NUM_OUT_BYTES	(NUM_OUT_PIXELS*2)
#define	NUM_OUT_LINES	(720)

// output buffer geometry
#define NUM_UYVY_PIXELS	(NUM_OUT_PIXELS*2)
#define NUM_UYVY_BYTES	(NUM_UYVY_PIXELS*1)
#define NUM_BGR_PIXELS	(NUM_OUT_PIXELS*3)
#define NUM_BGR_BYTES	(NUM_BGR_PIXELS*1)
// double lines out
#define	NUM_OUT_DLINES	(NUM_OUT_LINES>>1)

#endif /* IOFILES_SONY_DUALEXP_H */
