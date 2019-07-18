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
 * \file 		csi_func.hpp
 * \brief 	Mipi csi receiver and camera related functionality declaration.
 * \author 	Tomas Babinec
 * \version 0.1
 * \date 		21-September-2015
 ****************************************************************************/

#ifndef CAMFUNC_H
#define CAMFUNC_H

#ifdef __cplusplus 
extern "C" { 
#endif

#include "cam_types.h"

//****************************************************************************
// contant definitions
//****************************************************************************

//****************************************************************************
// types
//****************************************************************************

//****************************************************************************
// function declarations
//****************************************************************************

/****************************************************************************/
/** Initializes Generic camera driver.
 * 
 * \return CAM_DRV_SUCCESS if all ok,
 *         CAM_DRV_FAILURE otherwise.
 ****************************************************************************/
int32_t CAM_DRV_Setup(void);

/****************************************************************************/
/** Deinitialize the driver.
 * 
 * \return CAM_DRV_SUCCESS if all ok,
 *         CAM_DRV_FAILURE otherwise.
 ****************************************************************************/
int32_t CAM_DRV_Close(void);

/****************************************************************************/
/** Add a camera client with specified configuration.
 * 
 * \param apCfg new camera descrtiption 
 * 
 * \return Camera client handle if all ok,
 *         0 otherwise.
 ****************************************************************************/
CamI2cClient_t CAM_DRV_ClientAdd(const CamI2cCfg_t *const apCfg);

/****************************************************************************/
/** Remove specified camera client.
 * 
 * \param aClient handle to client
 * 
 * \return CAM_DRV_SUCCESS if all ok,
 *         CAM_DRV_FAILURE otherwise.
 ****************************************************************************/
int32_t CAM_DRV_ClientRem(const CamI2cClient_t aClient);


/****************************************************************************/
/** I2C write.
 * 
 * \param apXfr transfer description
 *
 * \return CAM_DRV_SUCCESS if all ok,
 *         CAM_DRV_FAILURE otherwise.
 ****************************************************************************/
int32_t CAM_DRV_Write(const I2cXfrSingle_t *apXfr);

/****************************************************************************/
/** I2C read.
 * 
 * \param apXfr transfer description
 *
 * \return CAM_DRV_SUCCESS if all ok,
 *         CAM_DRV_FAILURE otherwise.
 ****************************************************************************/
int32_t CAM_DRV_Read(I2cXfrSingle_t *apXfr);

/****************************************************************************/
/** I2C write to a register with a command .
 * 
 * \param apCam client struct
 * \param apCmd comand to be executed
 * 
 * \return CAM_DRV_SUCCESS if all ok,
 *         CAM_DRV_FAILURE otherwise.
 ****************************************************************************/
int32_t CAM_DRV_CmdWrite(const CamGeneric_t  *const apCam, 
                  I2cXfrWriteCmd_t *const apCmd);

/****************************************************************************/
/** Set up the number of I2C retransmission's repeat when I2C transmission is failed
 * 
 * \param aI2cRepeat the number of I2C retransmission's repeat
 *
 * \return CAM_DRV_SUCCESS if all ok,
 *         CAM_DRV_FAILURE otherwise.
 ****************************************************************************/
int32_t CAM_DRV_I2C_RepeatSet(const uint32_t aI2cRepeat);

/****************************************************************************/
/** Return the number of I2C retransmission's repeat
 * 
 * \param apI2cRepeat the address of variable which will store the current number of I2C transmission's repeat
 *
 * \return CAM_DRV_SUCCESS if all ok,
 *         CAM_DRV_FAILURE otherwise.
 ****************************************************************************/
int32_t CAM_DRV_I2C_RepeatGet(uint32_t *const apI2cRepeat);

/****************************************************************************/
/** Reset camera by setting pin defined in device tree
 * 
 * \param apPowerCtrlCmd structure contain command parameter, include camera type, sensor type, camera index. Power state is ignored in this function
 *
 * \return CAM_DRV_SUCCESS if all ok,
 *         CAM_DRV_FAILURE otherwise.
 ****************************************************************************/
int32_t CAM_DRV_Reset(CamResetPinCmd_t apPowerCtrlCmd);

/****************************************************************************/
/** Set/clear power pin of camera defined in device tree
 * 
 * \param apPowerCtrlCmd structure contain command parameter, include camera type, sensor type, camera index, new power state
 *
 * \return CAM_DRV_SUCCESS if all ok,
 *         CAM_DRV_FAILURE otherwise.
 ****************************************************************************/
int32_t CAM_DRV_Power_Control(CamPowerControlCmd_t apPowerCtrlCmd);
//*****************************************************************************

#ifdef __cplusplus 
} //extern "C" 
#endif

#endif /* CAMFUNC_H */
