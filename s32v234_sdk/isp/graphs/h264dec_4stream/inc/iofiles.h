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
 * \file    iofiles.h
 * \brief   ISP sony_y graph
 * \author  Armin Strobl
 * \author
 * \version 0.1
 * \date    12-05-2015
 * \note    inital version
 ****************************************************************************/

#ifndef	IOFILES_H
#define	IOFILES_H

#define	NUM_IN_LINES	808	// input image geometry
#define	NUM_IN_M1	(NUM_IN_LINES-1)
#define	NUM_IN_M2	(NUM_IN_LINES-2)
#define	NUM_IN_M4	(NUM_IN_LINES-4)
#define	NUM_IN_M6	(NUM_IN_LINES-6)
#define	NUM_IN_M8	(NUM_IN_LINES-8)
#define	NUM_LINES	NUM_IN_LINES
#define	NUM_OUT_LINES	800     // output image geometry

#endif /* IOFILES_H */
