/*****************************************************************************
 *
 * Copyright (c) 2017-2018 NXP
 * All Rights Reserved
 *
 *****************************************************************************
 *
 * THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/


#ifdef  __cplusplus
extern "C" {
#endif

#include "seq_graph.h"
#include "seq_graph_meta.h"

#include "mipi_simple_c.h"

#include "iofiles_mipi_simple.h"
#ifndef S32DS_BUILD
#include "kmem.c"
#endif
#include "kmem_sym.h"
// *** forwards needed for cross-linking ***

static SEQ_FdmaCfg_t FastDMA;
static SEQ_MipiCfg_t MIPI;
static SEQ_IpuCfg_t Debayer_RGB;
static SEQ_Load_t sCodedebayer_rgb_simple_interleaved_Debayer_RGB;

/*** Buffers ****************************************************************/

SEQ_Buf_t Debayer_RGBBuffer0_mipi_simple = {

  // *** buffer ***
  (SEQ_Mem_Ptr_t) 0,		// *** pointer to output buffer ***
  16,				// *** number of lines fitting into output buffer (wrap) ***
  3840 * 1,				// *** number of bytes per line to read ***
  BUF_ALIGN(3840),				// *** number of bytes to next line begin ***
#if defined(_SEQ_HAS_FILLLEVEL_)
  0,				// *** index of buffer input/producer incrementing the buffer fill level ***
#endif // if defined(_SEQ_HAS_FILLLEVEL_)
  // *** producer/write ***
  0,				// *** buffers status ***
  (SEQ_Head_Ptr_t) 20 /*Debayer_RGB*/,		// *** offset to producers (node) configuration header ***
  0,				// *** current relative index into output buffer (write) ***
  1,				// *** increment of current relative index ***
  0,				// *** total lines written to buffer ***
  0,				// *** pad alignment ***

  {
    // *** consumer/read #0 ***
    {
      (SEQ_Head_Ptr_t) 356 /* FastDMA.mHead */,	// *** offset to consumers (node) configuration header ***
      0,				// *** the devices channel used ***
      0,				// *** number of lines to skip at frame begin ***
      1,				// *** number of lines required for processing ***
      3840 * 1,				// *** number of bytes per line to read ***
      0,				// *** current relative index into source buffer (read) ***
      1,				// *** increment of current relative index ***
      0,				// *** total lines read from buffer ***
      0,				// *** buffer is ready to be read by this consumer ***
      0,				// *** maximum difference between read and write ***
      0,				// *** pad aligment ***
    },
    // *** consumer/read #1 ***
    {
      (SEQ_Head_Ptr_t) 0,		// *** pointer to consumers (node) configuration header ***
      0,				// *** the devices channel used ***
      0,				// *** number of lines to skip at frame begin ***
      0,				// *** number of lines required for processing ***
      0,				// *** number of bytes per line to read ***
      0,				// *** current relative index into source buffer (read) ***
      0,				// *** increment of current relative index ***
      0,				// *** total lines read from buffer ***
      0,				// *** buffer is ready to be read by this consumer ***
      0,				// *** maximum difference between read and write ***
      0,				// *** pad aligment ***
    },
    // *** consumer/read #2 ***
    {
      (SEQ_Head_Ptr_t) 0,		// *** pointer to consumers (node) configuration header ***
      0,				// *** the devices channel used ***
      0,				// *** number of lines to skip at frame begin ***
      0,				// *** number of lines required for processing ***
      0,				// *** number of bytes per line to read ***
      0,				// *** current relative index into source buffer (read) ***
      0,				// *** increment of current relative index ***
      0,				// *** total lines read from buffer ***
      0,				// *** buffer is ready to be read by this consumer ***
      0,				// *** maximum difference between read and write ***
      0,				// *** pad aligment ***
    },
    // *** consumer/read #3 ***
    {
      (SEQ_Head_Ptr_t) 0,		// *** pointer to consumers (node) configuration header ***
      0,				// *** the devices channel used ***
      0,				// *** number of lines to skip at frame begin ***
      0,				// *** number of lines required for processing ***
      0,				// *** number of bytes per line to read ***
      0,				// *** current relative index into source buffer (read) ***
      0,				// *** increment of current relative index ***
      0,				// *** total lines read from buffer ***
      0,				// *** buffer is ready to be read by this consumer ***
      0,				// *** maximum difference between read and write ***
      0,				// *** pad aligment ***
    },
    // *** consumer/read #4 ***
    {
      (SEQ_Head_Ptr_t) 0,		// *** pointer to consumers (node) configuration header ***
      0,				// *** the devices channel used ***
      0,				// *** number of lines to skip at frame begin ***
      0,				// *** number of lines required for processing ***
      0,				// *** number of bytes per line to read ***
      0,				// *** current relative index into source buffer (read) ***
      0,				// *** increment of current relative index ***
      0,				// *** total lines read from buffer ***
      0,				// *** buffer is ready to be read by this consumer ***
      0,				// *** maximum difference between read and write ***
      0,				// *** pad aligment ***
    },
    // *** consumer/read #5 ***
    {
      (SEQ_Head_Ptr_t) 0,		// *** pointer to consumers (node) configuration header ***
      0,				// *** the devices channel used ***
      0,				// *** number of lines to skip at frame begin ***
      0,				// *** number of lines required for processing ***
      0,				// *** number of bytes per line to read ***
      0,				// *** current relative index into source buffer (read) ***
      0,				// *** increment of current relative index ***
      0,				// *** total lines read from buffer ***
      0,				// *** buffer is ready to be read by this consumer ***
      0,				// *** maximum difference between read and write ***
      0,				// *** pad aligment ***
    },
    // *** consumer/read #6 ***
    {
      (SEQ_Head_Ptr_t) 0,		// *** pointer to consumers (node) configuration header ***
      0,				// *** the devices channel used ***
      0,				// *** number of lines to skip at frame begin ***
      0,				// *** number of lines required for processing ***
      0,				// *** number of bytes per line to read ***
      0,				// *** current relative index into source buffer (read) ***
      0,				// *** increment of current relative index ***
      0,				// *** total lines read from buffer ***
      0,				// *** buffer is ready to be read by this consumer ***
      0,				// *** maximum difference between read and write ***
      0,				// *** pad aligment ***
    },
    // *** consumer/read #7 ***
    {
      (SEQ_Head_Ptr_t) 0,		// *** pointer to consumers (node) configuration header ***
      0,				// *** the devices channel used ***
      0,				// *** number of lines to skip at frame begin ***
      0,				// *** number of lines required for processing ***
      0,				// *** number of bytes per line to read ***
      0,				// *** current relative index into source buffer (read) ***
      0,				// *** increment of current relative index ***
      0,				// *** total lines read from buffer ***
      0,				// *** buffer is ready to be read by this consumer ***
      0,				// *** maximum difference between read and write ***
      0,				// *** pad aligment ***
    },

  }
}; // Debayer_RGBBuffer0_mipi_simple

SEQ_Buf_t MIPIBuffer0_mipi_simple = {

  // *** buffer ***
  (SEQ_Mem_Ptr_t) 0,		// *** pointer to output buffer ***
  32,				// *** number of lines fitting into output buffer (wrap) ***
  1288 * 2,				// *** number of bytes per line to read ***
  BUF_ALIGN(2576),				// *** number of bytes to next line begin ***
#if defined(_SEQ_HAS_FILLLEVEL_)
  0,				// *** index of buffer input/producer incrementing the buffer fill level ***
#endif // if defined(_SEQ_HAS_FILLLEVEL_)
  // *** producer/write ***
  0,				// *** buffers status ***
  (SEQ_Head_Ptr_t) 320 /*MIPI*/,		// *** offset to producers (node) configuration header ***
  0,				// *** current relative index into output buffer (write) ***
  1,				// *** increment of current relative index ***
  0,				// *** total lines written to buffer ***
  0,				// *** pad alignment ***

  {
    // *** consumer/read #0 ***
    {
      (SEQ_Head_Ptr_t) 20 /* Debayer_RGB.mHead */,	// *** offset to consumers (node) configuration header ***
      0,				// *** the devices channel used ***
      0,				// *** number of lines to skip at frame begin ***
      2,				// *** number of lines required for processing ***
      1288 * 2,				// *** number of bytes per line to read ***
      0,				// *** current relative index into source buffer (read) ***
      1,				// *** increment of current relative index ***
      0,				// *** total lines read from buffer ***
      0,				// *** buffer is ready to be read by this consumer ***
      0,				// *** maximum difference between read and write ***
      0,				// *** pad aligment ***
    },
    // *** consumer/read #1 ***
    {
      (SEQ_Head_Ptr_t) 20 /* Debayer_RGB.mHead */,	// *** offset to consumers (node) configuration header ***
      1,				// *** the devices channel used ***
      0,				// *** number of lines to skip at frame begin ***
      2,				// *** number of lines required for processing ***
      1288 * 2,				// *** number of bytes per line to read ***
      0,				// *** current relative index into source buffer (read) ***
      1,				// *** increment of current relative index ***
      0,				// *** total lines read from buffer ***
      0,				// *** buffer is ready to be read by this consumer ***
      0,				// *** maximum difference between read and write ***
      0,				// *** pad aligment ***
    },
    // *** consumer/read #2 ***
    {
      (SEQ_Head_Ptr_t) 0,		// *** pointer to consumers (node) configuration header ***
      0,				// *** the devices channel used ***
      0,				// *** number of lines to skip at frame begin ***
      0,				// *** number of lines required for processing ***
      0,				// *** number of bytes per line to read ***
      0,				// *** current relative index into source buffer (read) ***
      0,				// *** increment of current relative index ***
      0,				// *** total lines read from buffer ***
      0,				// *** buffer is ready to be read by this consumer ***
      0,				// *** maximum difference between read and write ***
      0,				// *** pad aligment ***
    },
    // *** consumer/read #3 ***
    {
      (SEQ_Head_Ptr_t) 0,		// *** pointer to consumers (node) configuration header ***
      0,				// *** the devices channel used ***
      0,				// *** number of lines to skip at frame begin ***
      0,				// *** number of lines required for processing ***
      0,				// *** number of bytes per line to read ***
      0,				// *** current relative index into source buffer (read) ***
      0,				// *** increment of current relative index ***
      0,				// *** total lines read from buffer ***
      0,				// *** buffer is ready to be read by this consumer ***
      0,				// *** maximum difference between read and write ***
      0,				// *** pad aligment ***
    },
    // *** consumer/read #4 ***
    {
      (SEQ_Head_Ptr_t) 0,		// *** pointer to consumers (node) configuration header ***
      0,				// *** the devices channel used ***
      0,				// *** number of lines to skip at frame begin ***
      0,				// *** number of lines required for processing ***
      0,				// *** number of bytes per line to read ***
      0,				// *** current relative index into source buffer (read) ***
      0,				// *** increment of current relative index ***
      0,				// *** total lines read from buffer ***
      0,				// *** buffer is ready to be read by this consumer ***
      0,				// *** maximum difference between read and write ***
      0,				// *** pad aligment ***
    },
    // *** consumer/read #5 ***
    {
      (SEQ_Head_Ptr_t) 0,		// *** pointer to consumers (node) configuration header ***
      0,				// *** the devices channel used ***
      0,				// *** number of lines to skip at frame begin ***
      0,				// *** number of lines required for processing ***
      0,				// *** number of bytes per line to read ***
      0,				// *** current relative index into source buffer (read) ***
      0,				// *** increment of current relative index ***
      0,				// *** total lines read from buffer ***
      0,				// *** buffer is ready to be read by this consumer ***
      0,				// *** maximum difference between read and write ***
      0,				// *** pad aligment ***
    },
    // *** consumer/read #6 ***
    {
      (SEQ_Head_Ptr_t) 0,		// *** pointer to consumers (node) configuration header ***
      0,				// *** the devices channel used ***
      0,				// *** number of lines to skip at frame begin ***
      0,				// *** number of lines required for processing ***
      0,				// *** number of bytes per line to read ***
      0,				// *** current relative index into source buffer (read) ***
      0,				// *** increment of current relative index ***
      0,				// *** total lines read from buffer ***
      0,				// *** buffer is ready to be read by this consumer ***
      0,				// *** maximum difference between read and write ***
      0,				// *** pad aligment ***
    },
    // *** consumer/read #7 ***
    {
      (SEQ_Head_Ptr_t) 0,		// *** pointer to consumers (node) configuration header ***
      0,				// *** the devices channel used ***
      0,				// *** number of lines to skip at frame begin ***
      0,				// *** number of lines required for processing ***
      0,				// *** number of bytes per line to read ***
      0,				// *** current relative index into source buffer (read) ***
      0,				// *** increment of current relative index ***
      0,				// *** total lines read from buffer ***
      0,				// *** buffer is ready to be read by this consumer ***
      0,				// *** maximum difference between read and write ***
      0,				// *** pad aligment ***
    },

  }
}; // MIPIBuffer0_mipi_simple

SEQ_Buf_t FastDMA_OutBuffer_mipi_simple = {

  // *** buffer ***
  (SEQ_Mem_Ptr_t) 1,		// *** pointer to output buffer ***
  720,				// *** number of lines fitting into output buffer (wrap) ***
  3840 * 1,				// *** number of bytes per line to read ***
  5760,				// *** number of bytes to next line begin ***
#if defined(_SEQ_HAS_FILLLEVEL_)
  0,				// *** index of buffer input/producer incrementing the buffer fill level ***
#endif // if defined(_SEQ_HAS_FILLLEVEL_)
  // *** producer/write ***
  0,				// *** buffers status ***
  (SEQ_Head_Ptr_t) 356 /*FastDMA */,		// *** offset to producers (node) configuration header ***
  0,				// *** current relative index into output buffer (write) ***
  1,				// *** increment of current relative index ***
  0,				// *** total lines written to buffer ***
  0,				// *** pad alignment ***

  {
    // *** consumer/read #0 ***
    {
      (SEQ_Head_Ptr_t) 0,		// *** pointer to consumers (node) configuration header ***
      0,				// *** the devices channel used ***
      0,				// *** number of lines to skip at frame begin ***
      0,				// *** number of lines required for processing ***
      3840 * 1,				// *** number of bytes per line to read ***
      0,				// *** current relative index into source buffer (read) ***
      1,				// *** increment of current relative index ***
      0,				// *** total lines read from buffer ***
      0,				// *** buffer is ready to be read by this consumer ***
      0,				// *** maximum difference between read and write ***
      0,				// *** pad aligment ***
    },
    // *** consumer/read #1 ***
    {
      (SEQ_Head_Ptr_t) 0,		// *** pointer to consumers (node) configuration header ***
      0,				// *** the devices channel used ***
      0,				// *** number of lines to skip at frame begin ***
      0,				// *** number of lines required for processing ***
      0,				// *** number of bytes per line to read ***
      0,				// *** current relative index into source buffer (read) ***
      0,				// *** increment of current relative index ***
      0,				// *** total lines read from buffer ***
      0,				// *** buffer is ready to be read by this consumer ***
      0,				// *** maximum difference between read and write ***
      0,				// *** pad aligment ***
    },
    // *** consumer/read #2 ***
    {
      (SEQ_Head_Ptr_t) 0,		// *** pointer to consumers (node) configuration header ***
      0,				// *** the devices channel used ***
      0,				// *** number of lines to skip at frame begin ***
      0,				// *** number of lines required for processing ***
      0,				// *** number of bytes per line to read ***
      0,				// *** current relative index into source buffer (read) ***
      0,				// *** increment of current relative index ***
      0,				// *** total lines read from buffer ***
      0,				// *** buffer is ready to be read by this consumer ***
      0,				// *** maximum difference between read and write ***
      0,				// *** pad aligment ***
    },
    // *** consumer/read #3 ***
    {
      (SEQ_Head_Ptr_t) 0,		// *** pointer to consumers (node) configuration header ***
      0,				// *** the devices channel used ***
      0,				// *** number of lines to skip at frame begin ***
      0,				// *** number of lines required for processing ***
      0,				// *** number of bytes per line to read ***
      0,				// *** current relative index into source buffer (read) ***
      0,				// *** increment of current relative index ***
      0,				// *** total lines read from buffer ***
      0,				// *** buffer is ready to be read by this consumer ***
      0,				// *** maximum difference between read and write ***
      0,				// *** pad aligment ***
    },
    // *** consumer/read #4 ***
    {
      (SEQ_Head_Ptr_t) 0,		// *** pointer to consumers (node) configuration header ***
      0,				// *** the devices channel used ***
      0,				// *** number of lines to skip at frame begin ***
      0,				// *** number of lines required for processing ***
      0,				// *** number of bytes per line to read ***
      0,				// *** current relative index into source buffer (read) ***
      0,				// *** increment of current relative index ***
      0,				// *** total lines read from buffer ***
      0,				// *** buffer is ready to be read by this consumer ***
      0,				// *** maximum difference between read and write ***
      0,				// *** pad aligment ***
    },
    // *** consumer/read #5 ***
    {
      (SEQ_Head_Ptr_t) 0,		// *** pointer to consumers (node) configuration header ***
      0,				// *** the devices channel used ***
      0,				// *** number of lines to skip at frame begin ***
      0,				// *** number of lines required for processing ***
      0,				// *** number of bytes per line to read ***
      0,				// *** current relative index into source buffer (read) ***
      0,				// *** increment of current relative index ***
      0,				// *** total lines read from buffer ***
      0,				// *** buffer is ready to be read by this consumer ***
      0,				// *** maximum difference between read and write ***
      0,				// *** pad aligment ***
    },
    // *** consumer/read #6 ***
    {
      (SEQ_Head_Ptr_t) 0,		// *** pointer to consumers (node) configuration header ***
      0,				// *** the devices channel used ***
      0,				// *** number of lines to skip at frame begin ***
      0,				// *** number of lines required for processing ***
      0,				// *** number of bytes per line to read ***
      0,				// *** current relative index into source buffer (read) ***
      0,				// *** increment of current relative index ***
      0,				// *** total lines read from buffer ***
      0,				// *** buffer is ready to be read by this consumer ***
      0,				// *** maximum difference between read and write ***
      0,				// *** pad aligment ***
    },
    // *** consumer/read #7 ***
    {
      (SEQ_Head_Ptr_t) 0,		// *** pointer to consumers (node) configuration header ***
      0,				// *** the devices channel used ***
      0,				// *** number of lines to skip at frame begin ***
      0,				// *** number of lines required for processing ***
      0,				// *** number of bytes per line to read ***
      0,				// *** current relative index into source buffer (read) ***
      0,				// *** increment of current relative index ***
      0,				// *** total lines read from buffer ***
      0,				// *** buffer is ready to be read by this consumer ***
      0,				// *** maximum difference between read and write ***
      0,				// *** pad aligment ***
    },

  }
}; // FastDMA_OutBuffer_mipi_simple


static SEQ_CfgPara_t Debayer_RGBPara [] = {
{ D_IPUS_SYN_HOST_INACFG_OFF, 0x00000300 },
    { D_IPUS_SYN_HOST_XCFG_OFF, (1280 << 16) | 0x1 },
    { D_IPUS_SYN_HOST_OUTCFG_OFF, 0x00000100 },
    { D_IPUS_SYN_S_CH0_CFG_INA_OFF, 0x00058000 },
    { D_IPUS_SYN_S_CH1_CFG_INA_OFF, 0x00058000 },
    { D_IPUS_SYN_S_CH0_CFG_OUT_OFF, 0x10000000 },
};

static SEQ_MipiCfg_t MIPI = {
  {
    SEQ_NODE_OTHER,			// *** type of engine ***
    ISP_IO_DEV_BASE+ISP_OFFS_FILEIO+2*ISP_IO_DEV_SPACE*0,	// *** address of hardware device ***
    SEQ_OTHRIX_MIPICSI0,			// *** index of requested engine ***
    0,					// *** engine is running ***
    0,					// *** engine is done for this frame ***
    0,					// *** engine got some update ***
  },


  // *** output buffers ***
  {
      (SEQ_Buf_Ptr_t) 780 /*MIPIBuffer0_mipi_simple*/,			// *** pointer to output buffer ***
      (SEQ_Buf_Ptr_t) 0,			// *** pointer to output buffer ***
      (SEQ_Buf_Ptr_t) 0,			// *** pointer to output buffer ***
      (SEQ_Buf_Ptr_t) 0,			// *** pointer to output buffer ***
  },
  729,			// *** number of input image lines ***
  0			// *** pad alignment ***
}; // MIPI

static SEQ_IpuCfg_t Debayer_RGB = {
  {
    SEQ_NODE_SCALAR,			// *** type of engine ***
    D_IPUS_SYN_BASEADDRESS,		// *** address of hardware device ***
    0,			// *** index of requested engine *** (TODO resolve for -1)
    0,					// *** engine is running ***
    0,					// *** engine is done for this frame ***
    0,					// *** engine got some update ***
  },
  (0x00000000),			// *** code entry address ***

  0,					// *** current processing steps ***
  720,					// *** number of processing steps per frame ***

  {
    // *** output buffer # ***
    {
      (SEQ_Buf_Ptr_t) 564 /* Debayer_RGBBuffer0_mipi_simple */,			// *** pointer to output buffer ***
      {
        D_IPUS_SYN_S_LINE0_LEN_OUT_OFF,	// *** offset to SDMA's register ***
        0,					// *** number of first line to be used ***
        0,					// *** number of bytes to first pixel in line ***
        3840,					// *** number of pixels to transfer ***
      },
    },
    // *** output buffer # ***
    {
      (SEQ_Buf_Ptr_t) 0,			// *** pointer to output buffer ***
      {
        0,					// *** offset to SDMA's register ***
        0,					// *** number of first line to be used ***
        0,					// *** number of bytes to first pixel in line ***
        0,					// *** number of pixels to transfer ***
      },
    },
    // *** output buffer # ***
    {
      (SEQ_Buf_Ptr_t) 0,			// *** pointer to output buffer ***
      {
        0,					// *** offset to SDMA's register ***
        0,					// *** number of first line to be used ***
        0,					// *** number of bytes to first pixel in line ***
        0,					// *** number of pixels to transfer ***
      },
    },
    // *** output buffer # ***
    {
      (SEQ_Buf_Ptr_t) 0,			// *** pointer to output buffer ***
      {
        0,					// *** offset to SDMA's register ***
        0,					// *** number of first line to be used ***
        0,					// *** number of bytes to first pixel in line ***
        0,					// *** number of pixels to transfer ***
      },
    },
  },	// output buffer structs

  {
    // *** input buffer # ***
    {
      (SEQ_Buf_Ptr_t) 780 /* MIPIBuffer0_mipi_simple */,			// *** pointer to input buffer ***
      {
        D_IPUS_SYN_S_LINE0_LEN_INA_OFF,				// *** offset to SDMA's register ***
        0,					// *** number of first line to be used ***
        0,					// *** number of bytes to first pixel in line ***
        1288,					// *** number of pixels to transfer ***
      },
      0,				// *** our index in buffers consumer array ***
      0,				// *** pad alignment ***
    },
    // *** input buffer # ***
    {
      (SEQ_Buf_Ptr_t) 780 /* MIPIBuffer0_mipi_simple */,			// *** pointer to input buffer ***
      {
        D_IPUS_SYN_S_LINE1_LEN_INA_OFF,				// *** offset to SDMA's register ***
        1,					// *** number of first line to be used ***
        0,					// *** number of bytes to first pixel in line ***
        1288,					// *** number of pixels to transfer ***
      },
      1,				// *** our index in buffers consumer array ***
      0,				// *** pad alignment ***
    },
    // *** input buffer # ***
    {
      (SEQ_Buf_Ptr_t) 0,				// *** pointer to input buffer ***
      {
        0,					// *** offset to SDMA's register ***
        0,					// *** number of first line to be used ***
        0,					// *** number of bytes to first pixel in line ***
        0,					// *** number of pixels to transfer ***
      },
      0,				// *** our index in buffers consumer array ***
      0,				// *** pad alignment ***
    },
    // *** input buffer # ***
    {
      (SEQ_Buf_Ptr_t) 0,				// *** pointer to input buffer ***
      {
        0,					// *** offset to SDMA's register ***
        0,					// *** number of first line to be used ***
        0,					// *** number of bytes to first pixel in line ***
        0,					// *** number of pixels to transfer ***
      },
      0,				// *** our index in buffers consumer array ***
      0,				// *** pad alignment ***
    },
    // *** input buffer # ***
    {
      (SEQ_Buf_Ptr_t) 0,				// *** pointer to input buffer ***
      {
        0,					// *** offset to SDMA's register ***
        0,					// *** number of first line to be used ***
        0,					// *** number of bytes to first pixel in line ***
        0,					// *** number of pixels to transfer ***
      },
      0,				// *** our index in buffers consumer array ***
      0,				// *** pad alignment ***
    },
    // *** input buffer # ***
    {
      (SEQ_Buf_Ptr_t) 0,				// *** pointer to input buffer ***
      {
        0,					// *** offset to SDMA's register ***
        0,					// *** number of first line to be used ***
        0,					// *** number of bytes to first pixel in line ***
        0,					// *** number of pixels to transfer ***
      },
      0,				// *** our index in buffers consumer array ***
      0,				// *** pad alignment ***
    },
    // *** input buffer # ***
    {
      (SEQ_Buf_Ptr_t) 0,				// *** pointer to input buffer ***
      {
        0,					// *** offset to SDMA's register ***
        0,					// *** number of first line to be used ***
        0,					// *** number of bytes to first pixel in line ***
        0,					// *** number of pixels to transfer ***
      },
      0,				// *** our index in buffers consumer array ***
      0,				// *** pad alignment ***
    },
    // *** input buffer # ***
    {
      (SEQ_Buf_Ptr_t) 0,				// *** pointer to input buffer ***
      {
        0,					// *** offset to SDMA's register ***
        0,					// *** number of first line to be used ***
        0,					// *** number of bytes to first pixel in line ***
        0,					// *** number of pixels to transfer ***
      },
      0,				// *** our index in buffers consumer array ***
      0,				// *** pad alignment ***
    },
    // *** input buffer # ***
    {
      (SEQ_Buf_Ptr_t) 0,				// *** pointer to input buffer ***
      {
        0,					// *** offset to SDMA's register ***
        0,					// *** number of first line to be used ***
        0,					// *** number of bytes to first pixel in line ***
        0,					// *** number of pixels to transfer ***
      },
      0,				// *** our index in buffers consumer array ***
      0,				// *** pad alignment ***
    },
  },	// input buffer structs
  (SEQ_CfgPara_CPtr_t) 244 /*Debayer_RGBPara */,	// *** pointer to configuration parameters ***
  6,					// *** number of configuration parameters following ***
  0,				// *** pad alignment ***
};

static SEQ_FdmaCfg_t FastDMA = {
  {
    SEQ_NODE_OTHER,			// *** type of engine ***
    (Addr_t)(uintptr_t)&FDMA,	// *** address of hardware device ***
    SEQ_OTHRIX_FDMA,			// *** index of requested engine ***
    0,					// *** engine is running ***
    0,					// *** engine is done for this frame ***
    0,					// *** engine got some update ***
  },

  {
    // *** output buffer #0 ***
    {
      (SEQ_Buf_Ptr_t) 996 /* FastDMA_OutBuffer_mipi_simple */,	// *** offset to destination buffer ***
    },

    // *** output buffer #1 ***
    {
      (SEQ_Buf_Ptr_t) 0,			// *** pointer to destination buffer ***
    },

    // *** output buffer #2 ***
    {
      (SEQ_Buf_Ptr_t) 0,			// *** pointer to destination buffer ***
    },

    // *** output buffer #3 ***
    {
      (SEQ_Buf_Ptr_t) 0,			// *** pointer to destination buffer ***
    },

    // *** output buffer #4 ***
    {
      (SEQ_Buf_Ptr_t) 0,			// *** pointer to destination buffer ***
    },

    // *** output buffer #5 ***
    {
      (SEQ_Buf_Ptr_t) 0,			// *** pointer to destination buffer ***
    },

    // *** output buffer #6 ***
    {
      (SEQ_Buf_Ptr_t) 0,			// *** pointer to destination buffer ***
    },

    // *** output buffer #7 ***
    {
      (SEQ_Buf_Ptr_t) 0,			// *** pointer to destination buffer ***
    },

    // *** output buffer #8 ***
    {
      (SEQ_Buf_Ptr_t) 0,			// *** pointer to destination buffer ***
    },

    // *** output buffer #9 ***
    {
      (SEQ_Buf_Ptr_t) 0,			// *** pointer to destination buffer ***
    },

    // *** output buffer #10 ***
    {
      (SEQ_Buf_Ptr_t) 0,			// *** pointer to destination buffer ***
    },

    // *** output buffer #11 ***
    {
      (SEQ_Buf_Ptr_t) 0,			// *** pointer to destination buffer ***
    },

    // *** output buffer #12 ***
    {
      (SEQ_Buf_Ptr_t) 0,			// *** pointer to destination buffer ***
    },

    // *** output buffer #13 ***
    {
      (SEQ_Buf_Ptr_t) 0,			// *** pointer to destination buffer ***
    },

    // *** output buffer #14 ***
    {
      (SEQ_Buf_Ptr_t) 0,			// *** pointer to destination buffer ***
    },

    // *** output buffer #15 ***
    {
      (SEQ_Buf_Ptr_t) 0,			// *** pointer to destination buffer ***
    },

  },

  // ### inputs ###############################################################

  {
    {
      // *** input buffer #0 ***
      (SEQ_Buf_Ptr_t) 564 /* Debayer_RGBBuffer0_mipi_simple */,	// *** input buffer ***
      0, 					// *** index into buffers consumer array ***
      0, 				// *** line offset ***
    },

    {
      // *** input buffer #1 ***
      (SEQ_Buf_Ptr_t) 0,			// *** input buffer ***
      0, 					// *** index into buffers consumer array ***
      0, 				// *** line offset ***
    },

    {
      // *** input buffer #2 ***
      (SEQ_Buf_Ptr_t) 0,			// *** input buffer ***
      0, 					// *** index into buffers consumer array ***
      0, 				// *** line offset ***
    },

    {
      // *** input buffer #3 ***
      (SEQ_Buf_Ptr_t) 0,			// *** input buffer ***
      0, 					// *** index into buffers consumer array ***
      0, 				// *** line offset ***
    },

    {
      // *** input buffer #4 ***
      (SEQ_Buf_Ptr_t) 0,			// *** input buffer ***
      0, 					// *** index into buffers consumer array ***
      0, 				// *** line offset ***
    },

    {
      // *** input buffer #5 ***
      (SEQ_Buf_Ptr_t) 0,			// *** input buffer ***
      0, 					// *** index into buffers consumer array ***
      0, 				// *** line offset ***
    },

    {
      // *** input buffer #6 ***
      (SEQ_Buf_Ptr_t) 0,			// *** input buffer ***
      0, 					// *** index into buffers consumer array ***
      0, 				// *** line offset ***
    },

    {
      // *** input buffer #7 ***
      (SEQ_Buf_Ptr_t) 0,			// *** input buffer ***
      0, 					// *** index into buffers consumer array ***
      0, 				// *** line offset ***
    },

    {
      // *** input buffer #8 ***
      (SEQ_Buf_Ptr_t) 0,			// *** input buffer ***
      0, 					// *** index into buffers consumer array ***
      0, 				// *** line offset ***
    },

    {
      // *** input buffer #9 ***
      (SEQ_Buf_Ptr_t) 0,			// *** input buffer ***
      0, 					// *** index into buffers consumer array ***
      0, 				// *** line offset ***
    },

    {
      // *** input buffer #10 ***
      (SEQ_Buf_Ptr_t) 0,			// *** input buffer ***
      0, 					// *** index into buffers consumer array ***
      0, 				// *** line offset ***
    },

    {
      // *** input buffer #11 ***
      (SEQ_Buf_Ptr_t) 0,			// *** input buffer ***
      0, 					// *** index into buffers consumer array ***
      0, 				// *** line offset ***
    },

    {
      // *** input buffer #12 ***
      (SEQ_Buf_Ptr_t) 0,			// *** input buffer ***
      0, 					// *** index into buffers consumer array ***
      0, 				// *** line offset ***
    },

    {
      // *** input buffer #13 ***
      (SEQ_Buf_Ptr_t) 0,			// *** input buffer ***
      0, 					// *** index into buffers consumer array ***
      0, 				// *** line offset ***
    },

    {
      // *** input buffer #14 ***
      (SEQ_Buf_Ptr_t) 0,			// *** input buffer ***
      0, 					// *** index into buffers consumer array ***
      0, 				// *** line offset ***
    },

    {
      // *** input buffer #15 ***
      (SEQ_Buf_Ptr_t) 0,			// *** input buffer ***
      0, 					// *** index into buffers consumer array ***
      0, 				// *** line offset ***
    },

  },
}; // FastDMA

static SEQ_Load_t sCodedebayer_rgb_simple_interleaved_Debayer_RGB = {
  {
    SEQ_NODE_FWLOAD,			// *** type of engine ***
    D_IPUS_SYN_BASEADDRESS,		// *** address of hardware device ***
    0,			// *** index of requested engine *** (TODO resolve for -1)
    0,					// *** engine is running ***
    0,					// *** engine is done for this frame ***
    0,					// *** engine got some update ***
  },

  debayer_rgb_simple_interleaved_start,		// *** Kernel address in KMEM *** 
  debayer_rgb_simple_interleaved_end - debayer_rgb_simple_interleaved_start,	// *** Kernel length in bytes ***
  (0x00000000) / 4,	// *** Kernel address in IPU instruction mem ***
  0,				// *** pad alignment ***
  (SEQ_Head_Ptr_t) 20 /* Debayer_RGB.mHead */,			// *** pointer to IPU node to start ***
};


/*****************************************************************************
* exported data
*****************************************************************************/

// *** graph ***

SEQ_Head_Ptr_t gpGraph_mipi_simple[] = {
  (SEQ_Head_Ptr_t) 356, // FastDMA
  (SEQ_Head_Ptr_t) 320, // MIPI
  (SEQ_Head_Ptr_t) 20, // Debayer_RGB
  (SEQ_Head_Ptr_t) 292, // sCodedebayer_rgb_simple_interleaved_Debayer_RGB
  (SEQ_Head_Ptr_t) 0		// ** END ***
};

// *** Graph parsing metadata ***

static Object_t sObjectList[9] = {
  { &gpGraph_mipi_simple,	20,	0 },
  { &Debayer_RGB,	224,	20 },
  { &Debayer_RGBPara,	48,	244 },
  { &sCodedebayer_rgb_simple_interleaved_Debayer_RGB,	28,	292 },
  { &MIPI,	36,	320 },
  { &FastDMA,	208,	356 },
  { &Debayer_RGBBuffer0_mipi_simple,	216,	564 },
  { &MIPIBuffer0_mipi_simple,	216,	780 },
  { &FastDMA_OutBuffer_mipi_simple,	216,	996 },
};

static uint32_t sPointerList[] = {
  0, /* gpGraph: pointer to FastDMA */
  4, /* gpGraph: pointer to MIPI */
  8, /* gpGraph: pointer to Debayer_RGB */
  12, /* gpGraph: pointer to sCodedebayer_rgb_simple_interleaved_Debayer_RGB */
  44, /* Debayer_RGB: pointer to OUTput buffer */
  92, /* Debayer_RGB: pointer to INput buffer */
  108, /* Debayer_RGB: pointer to INput buffer */
  236, /* Debayer_RGB: pointer to config parameters */
  316, /* sCodedebayer_rgb_simple_interleaved_Debayer_RGB: pointer to Debayer_RGB.mHead */
  336, /* MIPI: pointer to OUTput buffer */
  576, /* Debayer_RGBBuffer0_mipi_simple: pointer to producer */
  588, /* Debayer_RGBBuffer0_mipi_simple: pointer to consumer */
  792, /* MIPIBuffer0_mipi_simple: pointer to producer */
  804, /* MIPIBuffer0_mipi_simple: pointer to consumer */
  828, /* MIPIBuffer0_mipi_simple: pointer to consumer */
  1008, /* FastDMA_OutBuffer_mipi_simple: pointer to producer */
};

static uint32_t sBufferList[] = {
  564, /* Debayer_RGBBuffer0_mipi_simple */
  780, /* MIPIBuffer0_mipi_simple */
  996, /* FastDMA_OutBuffer_mipi_simple */
};

static const char* scppFdmaChannelNames[] = {
  "FastDMA_Out",
};

static const char* scppBufferNames[] = {
  "Debayer_RGBBuffer0_mipi_simple",
  "MIPIBuffer0_mipi_simple",
  "FastDMA_OutBuffer_mipi_simple",
};

GraphMetadata_t gGraphMetadata_mipi_simple = {
  8,		// *** max number of buffer consumers
  1212,		// *** graph size [bytes]
  (const Object_t*) &sObjectList,	// *** object list pointer
  9,		// *** object count
  (const uint32_t*) &sPointerList,	// *** pointer list pointer
  16,		// *** pointer count
  (const uint32_t*) &sBufferList,	// *** buffer list pointer
  3,		// *** buffer count
  {
    0
  },
  { // MIPI-CSI metadata
    { // node MIPI
      CSI_SONY224, 1,
      {
        0, 0, 0, 0,
      },
      {
        1288 * 2, 0, 0, 0,
      }
    },
    { // node not used
      CSI_NONE, 0, {0}, {0}
    },
  },
  { // VIU Lite metadata
    { // node not used
      VIU_NONE, 0, 0
    },
    { // node not used
      VIU_NONE, 0, 0
    },
  },
  scppFdmaChannelNames,
  scppBufferNames
};

#ifdef  __cplusplus
}
#endif

/*EOF*/
