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
/*==============================================================================
Revision History:
                        Modification       Tracking
Author (core ID)        Date D/M/Y         Number     Description of Changes
Tomas Babinec           03-Nov-2014                   Init version
Nguyen Tri Hai(B51945)  1-Dec-2017        VSDK-1225   Resolve Misra violations
==============================================================================*/
/**
* \file     isp_csi.h
* \brief    public declarations for MIPI-CSI user space library
* \author   Tomas Babinec
* \version  0.1
* \date     03-November-2014
* \note
****************************************************************************/

#ifndef CSIPUBLIC_H
#define CSIPUBLIC_H

#include "../libs/isp/csi/kernel/include/csi.h"

//*****************************************************************************
// constants
//*****************************************************************************


//*****************************************************************************
// types
//*****************************************************************************

/****************************************************************************/
/** CSI user space library return values.
 * 
 ****************************************************************************/
enum CSI_LIB_RESULT
{
  CSI_LIB_SUCCESS = 0,
  CSI_LIB_FAILURE = 1
}; // CSI_LIB_RESULT

/****************************************************************************/
///< Pointer to a user function handling CSI events
typedef void(*CSI_EventHandler_t)(uint32_t aEventType);

/****************************************************************************/
/** CSI even handler class
 * 
 ****************************************************************************/
class CSI_EventHandlerClass
{
protected:
  CSI_EventHandlerClass &operator=( CSI_EventHandlerClass const &) = default;    
public:
  virtual void CsiEventHandler(uint32_t aEventType) = 0;
}; // CSI_EventHandlerClass

//*****************************************************************************
// public functionality declarations
//*****************************************************************************

/****************************************************************************/
/** Prepares the CSI driver to be used.
 *
 * In Linux the csi special device file is opened.
 * In standalone environment the CSI_SetUp() function is called directly to
 * initialize the internal driver structures and CSI HW.
 * 
 * \return CSI_LIB_SUCCESS if all ok
 *         CSI_LIB_FAILURE if opening of the device file fails
 ****************************************************************************/
CSI_LIB_RESULT CSI_Open(void);

/****************************************************************************/
/** Deinitializes the CSI driver use.
 * 
 * In Linux the csi special device file is closed.
 * In standalone environment the CSI_Close() function is called directly to
 * release internal driver resources and disconnect from the HW.
 * 
 * \return CSI_LIB_SUCCESS if all ok
 *         CSI_LIB_FAILURE if the close fails
 ****************************************************************************/
CSI_LIB_RESULT CSI_Close(void);

/****************************************************************************/
/** Configures CSI registers.
 * 
 * \param apcCsiCfg structure describing the configuration
 * 
 * \return CSI_LIB_SUCCESS if all ok
 *         CSI_LIB_FAILURE otherwise
 ****************************************************************************/
CSI_LIB_RESULT CSI_Config(CSI_Cfg_t * const apcCsiCfg);

/****************************************************************************/
/** Configures CSI embedded data reception.
 * 
 * \param arEmbdCfg structure describing the configuration
 * 
 * \return CSI_LIB_SUCCESS if all ok
 *         CSI_LIB_FAILURE otherwise
 ****************************************************************************/
CSI_LIB_RESULT CSI_EmbdConfig(const CSI_EmbdCfg_t &arEmbdCfg);

/****************************************************************************/
/** Requests embedded data to be recaptured.
 * 
 * \param acCsiIdx index of the CSI interface to capture the data from
 * 
 ****************************************************************************/
CSI_LIB_RESULT CSI_EmbdRecap(const enum CSI_IDX acCsiIdx);

/****************************************************************************/
/** Gets status of embedded data capturing.
 * 
 * \param arEmbdStatus structure to be filled with embedded status
 * \param acCsiIdx index of the CSI interface to capture the data from
 * 
 * \return CSI_LIB_SUCCESS if all ok
 *         CSI_LIB_FAILURE otherwise
 ****************************************************************************/
CSI_LIB_RESULT CSI_EmbdStatusGet(CSI_EmbdStatus_t &arEmbdStatus,
                                 const enum CSI_IDX acCsiIdx);

/****************************************************************************/
/** Gets CSI error status.
 * 
 * \param arErrStatus structure to be filled with error status
 * \param acCsiIdx index of the CSI interface to capture the data from
 * 
 * \return CSI_LIB_SUCCESS if all ok
 *         CSI_LIB_FAILURE otherwise
 ****************************************************************************/
CSI_LIB_RESULT CSI_ErrStatusGet(CSI_ErrStatus_t &arErrStatus, 
                                const enum CSI_IDX acCsiIdx);

/****************************************************************************/
/** Clears all CSI error captured so far and reenables detection.
 * 
 * \note Only first detected error is signaled through RT signal. CSI_ErrClear
 *       reenables the signaling.
 * 
 * \param arErrStatus structure to be filled with error status
 * \param acCsiIdx index of the CSI interface to capture the data from
 * 
 * \return CSI_LIB_SUCCESS if all ok
 *         CSI_LIB_FAILURE otherwise
 ****************************************************************************/
CSI_LIB_RESULT CSI_ErrClear(const enum CSI_IDX acCsiIdx);

/****************************************************************************/
/** Enables CSI receiver.
 * 
 * \param aCsiIdKey[in] Identifies CSI interface channels to Configures
 * 
 * \return CSI_LIB_SUCCESS if all ok
 *         CSI_LIB_FAILURE otherwise
 ****************************************************************************/
CSI_LIB_RESULT CSI_Start(CSI_IdKey_t const aCsiIdKey);

/****************************************************************************/
/** Disables CSI receiver.
 * 
 * \param aCsiIdKey[in] Identifies CSI interface channels to Configures
 * 
 * \return CSI_LIB_SUCCESS if all ok
 *         CSI_LIB_FAILURE otherwise
 ****************************************************************************/
CSI_LIB_RESULT CSI_Stop(CSI_IdKey_t const aCsiIdKey);

/****************************************************************************/
/** Requests CSI soft reset.
 * Resets CSI HW registers to default values, FIFOs will be flushed.
 * 
 * \param aCsiIdx[in] Identifies CSI interface
 * 
 * \return CSI_LIB_SUCCESS if all ok
 *         CSI_LIB_FAILURE otherwise
 ****************************************************************************/
CSI_LIB_RESULT CSI_SwReset(CSI_IDX_t const aCsiIdx);

/****************************************************************************/
/** Register event handler.
 * NULL is a valid parameter. Removes the previous handler.
 * 
 * \param aHandler user defined CSI event handling function
 * 
 * \return CSI_LIB_SUCCESS if all ok
 *         CSI_LIB_FAILURE if opening of the device file fails
 ****************************************************************************/
CSI_LIB_RESULT CSI_EventHandlerSet(CSI_EventHandler_t aHandler);

/****************************************************************************/
/** Register event handler object.
 * NULL is a valid parameter. Removes the previous handler.
 * 
 * \param arHandler user defined Sequencer event handling object
 * 
 * \return CSI_LIB_SUCCESS if all ok
 *         CSI_LIB_FAILURE if opening of the device file fails
 ****************************************************************************/
CSI_LIB_RESULT CSI_EventHandlerSet(CSI_EventHandlerClass * const apHandler);

#ifdef __STANDALONE__
void CSI_IrqHandlerSet(enum CSI_IDX aCsiIdx, void (*apIrqHandler)(void));
#endif // ifdef __STANDALONE__

#endif /* CSIPUBLIC_H */

//****************************************************************************
/* EOF */