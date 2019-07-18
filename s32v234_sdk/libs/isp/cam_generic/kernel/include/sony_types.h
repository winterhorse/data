/*
 * Copyright (c) 2016 Freescale Semiconductor
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/**
* \file     sony_types.h
* \brief    types declarations for Sony_IMX224 camera driver
* \author   Tomas Babinec
* \version  0.1
* \date     20.10.2015
* \note
****************************************************************************/
#ifndef SONYTYPES_H
#define SONYTYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(__KERNEL__) && !defined(__STANDALONE__)
#include <stdint.h>

#endif // if !defined(__KERNEL__) && !defined(__STANDALONE__)

#include "cam_types.h"

//*****************************************************************************
// CONST
//*****************************************************************************
#define SONY_SINGLE_EXP ((uint8_t)1)
#define SONY_DUAL_EXP   ((uint8_t)2)

#define SONY_MASTER     0
#define SONY_SLAVE      1

#define SONY_CROP       0 ///< cropping mode (set by default)
#define SONY_720P       1
#define SONY_QVGA       2

#define SONY_EXP_AG 1       ///< analog gain flag
#define SONY_EXP_EL 2       ///< exposure lines flag
#define SONY_EXP_CG 4       ///< conversion gain flag

#define SONY_RESET_POLARITY 0  // active low
#define SONY_RESET_DELAY    10
#define SONY_PWDN_POLARITY  0  // active low
#define SONY_PWDN_DELAY     10
//*****************************************************************************
// types
//*****************************************************************************

typedef struct SONY_Geometry
{
  enum CSI_IDX mCsiIdx; ///< CSI interface IDX

  // window mode
  uint32_t mWinMode; ///< SONY_QVGA, SONY_720P, SONY_CROP

  // frame max geometry
  uint32_t mVmax;   ///< maximum number of lines
  uint32_t mHmax;   ///< maximum number of pulses per line, only for readout

  // ROI
  uint32_t mXoff;
  uint32_t mYoff;
  uint32_t mWidth;
  uint32_t mHeight;
  uint8_t  mOb;     ///< optical black lines <6;16>

  // image flip
  uint8_t mVerFlip;
  uint8_t mHorFlip;

  // FPS
  uint8_t mFps;     ///< frames per second

  // single/dual exposure
  uint8_t mExpMode; ///< SONY_SINGLE_EXP or SONY_DUAL_EXP

  // master/slave
  uint8_t mSyncMode;  ///< SONY_MASTER or SONY_SLAVE

} SONY_Geometry_t;

//*****************************************************************************

typedef struct SONY_Exposure
{
  enum CSI_IDX mCsiIdx; ///< CSI interface IDX

  uint32_t mAnalogGain;          ///< 0 <-> 72dB; <0; 720>
  uint32_t mExposureLines;       ///< <0; VMAX>
  uint32_t mExposureLinesShort;  ///< <0; VMAX>
  uint8_t  mConversionGain;      ///< Low, High; <0; 1>

  uint8_t mConfigFlags;     ///< what should be set; all if 0
} SONY_Exposure_t;

//*****************************************************************************

typedef enum SONY_ExpState
{
  SONY_EXP_SENT = 1,  ///< exposure update sent through i2c
  SONY_EXP_APPLIED,   ///< exposure update applied to registers
  SONY_EXP_USED,      ///< exposure update used for latest frame
  SONY_EXP_READY,     ///< exposure ready to be updated again
}  SONY_ExpState_t;

//*****************************************************************************

typedef struct SONY_ChGain
{
  enum CSI_IDX mCsiIdx;     ///< CSI interface IDX

  uint16_t mLevel[4];       ///< one per channel
  uint16_t mMax;            ///< maximum Level
  uint16_t mMin;            ///< minium Level

}  SONY_ChGain_t;

//*****************************************************************************

#ifdef __cplusplus
} //extern "C"
#endif

#endif /* SONYTYPES_H */