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

#ifndef FRAMEIOTYPES_H
#define FRAMEIOTYPES_H

#include <stdint.h>

namespace io
{
  typedef enum 
  {
    IO_DATA_DEPTH_08 = 1,
    IO_DATA_DEPTH_16 = 2,
    IO_DATA_DEPTH_32 = 4,
    IO_DATA_DEPTH_64 = 8,
    IO_DATA_DEPTH_NOT_INITIALIZED
  } IO_DATA_DEPTH;
  
  typedef enum 
  {
    IO_DATA_CH1 = 1,
    IO_DATA_CH2,
    IO_DATA_CH3,
    IO_DATA_CH4,
    IO_DATA_CH_NOT_INITIALIZED,
  } IO_DATA_CHANNELS; 
  
  typedef enum 
  {
    IO_OK = 0,
    IO_EOF,
    IO_ERROR
  } IO_STATUS; 
}

#endif /* FRAMEIOTYPES_H */