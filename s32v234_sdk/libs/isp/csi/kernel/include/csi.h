/*
 * Copyright (c) 2014-2016 Freescale Semiconductor
 * Copyright (c) 2017-2018 NXP
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

/*==============================================================================
Revision History:
                        Modification       Tracking
Author (core ID)        Date D/M/Y         Number     Description of Changes
Tomas Babinec           28-Apr-2016                   Init version
Nguyen Tri Hai(B51945)  1-Dec-2017        VSDK-1225   Resolve Misra violations
Tomas Babinec           03-Jan-2018       VSDK-1624   LLD CMD
==============================================================================*/
#ifndef CSI_H
#define CSI_H

#ifdef __cplusplus
extern "C" {
#endif

/**
* \file     csi.h
* \brief    declarations for csi driver
*/

/*==============================================================================
*                             INCLUDE FILES
==============================================================================*/

#include "isp_hw.h"
#include "csi_types.h"

#if !defined(__STANDALONE__)
  #include "csi_types.h"
# endif // !defined(__STANDALONE__)
/*==============================================================================
*                             CONSTANTS
==============================================================================*/

/*==============================================================================
*                             DEFINES AND MACROS
==============================================================================*/

// errpr signal number
#define CSI_ERR_SIGNAL  55

// IRQ GIC ids
#define CSI0_ERR_IRQ    123
#define CSI1_ERR_IRQ    124
#define CSI0_FRM_IRQ    125
#define CSI1_FRM_IRQ    126

// CSI driver return values
#define CSI_DRV_SUCCESS    0
#define CSI_DRV_FAILURE   -1

// I2C definitions if not Standalone
#ifndef __STANDALONE__
  #define I2C0      0
  #define I2C1      1
  #define I2C2      2
#endif // #ifndef __STANDALONE__

// name of the device file
#define CSI_DEVICE_NAME "csi"

// magic number for CSI driver
// 0x63 is corresponding to 'c'
#define CSI_IOC_MAGIC   0x63U

#define SIUL2_BASE      0x4006C000UL
/*==============================================================================
*                                  ENUMS
==============================================================================*/

/*==============================================================================
*                        STRUCTURES AND OTHER TYPEDEFS
==============================================================================*/

/*==============================================================================
*                        GLOBAL VARIABLE DECLARATIONS
==============================================================================*/

/*=============================================================================
*                              FUNCTION PROTOTYPES
==============================================================================*/

#ifdef __cplusplus
} //extern "C"
#endif

#endif /* CSI_H */
