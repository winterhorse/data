 /*
 * Copyright 2012-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * o Neither the name of NXP nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*==============================================================================
*                                 INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==============================================================================*/

/**
* @file            h264dcd_linux.c
*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/dma-mapping.h>
#include <linux/interrupt.h>
#include <linux/clk.h>
#include <linux/of_platform.h>
#include <linux/uaccess.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <video/of_display_timing.h>
#include <video/videomode.h>
#include <linux/pm_runtime.h>

#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/errno.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#include <linux/of_net.h>
#include <linux/cdev.h>
#include <asm/current.h>
#include <asm/segment.h>
#include <linux/uaccess.h>

#include "h264dcd_linux.h"
#include "h264dcd_types.h"
#include "h264dcd_core.h"
#include "os_oal.h"

#include "vdb_log.h"

/*==============================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==============================================================================*/


/*==============================================================================
*                               LOCAL MACROS
==============================================================================*/
#define DEVICE_NAME "h264dcd"
#define DRIVER_NAME "h264decoder"

#define IPG_CLK "ipg"
#define B_CLK "bclock"

/**********************************************************
 * Macros for tracing
 **********************************************************/
#define H264DCD_INFO    KERN_INFO
#define __LOG_TRACE__   0

#if __LOG_TRACE__
  #define __TRACE__() printk(H264DCD_INFO "[ H264DCD ] %s\n", __func__)
  #define __MSG_TRACE__(string, args...) printk(H264DCD_INFO \
      "[ h264DCD ]  %s : %d : " string, __func__, __LINE__, ##args)
#else
  #define __TRACE__()
  #define __MSG_TRACE__(string, args...)
  #define __HERE__ printk(H264DCD_INFO " HERE %s\n", __func__)
#endif


/*==============================================================================
*                               GLOBAL VARIABLE
==============================================================================*/

static void __iomem * h264dcd_reg_base;

struct h264dcd_data {
  struct cdev     chdev;
  uint32_t        irq;
  struct clk      *h264dcd_clk;
  struct clk      *ipg_clk;
  struct clk      *b_clk;
  atomic_t        access;
};

static struct class *h264dcd_class;
static dev_t        h264dcd_devn; /*__u32 */

/*==============================================================================
*                           LOCAL FUNCTION PROTOTYPES
==============================================================================*/
static int32_t h264dcd_remove(struct platform_device *pdev);
static int32_t h264dcd_probe(struct platform_device *pdev);
static int32_t h264dcd_open(struct inode *inod, struct file *pfile);
static int32_t h264dcd_close(struct inode *inod, struct file *pfile);
static int32_t h264dcd_dev_create(void);

/*==============================================================================
*                               LOCAL FUNCTIONS
==============================================================================*/

/*==============================================================================
*                                GLOBAL FUNCTIONS
==============================================================================*/

/*============================================================================*/
/**
* @brief          The function manipulates the underlying device parameters.
* @details        The function manipulates the underlying device parameters of
*                 special file. Many operating characteristics of character
*                 special file may be controlled with h264dcd_lldcmd() requests.
*
* @param[in]      pcmd     LLD command structure pointer
* @return         long
* @api
* @isr
*
* @pre
*
* @post
*
* @note
*/
static int64_t h264dcd_lldcmd(OAL_LldCmd_t* pcmd)
{
  int32_t ret = 0;
  H264DCD_REGS* reg_base = (H264DCD_REGS *) h264dcd_reg_base;

  __TRACE__();

  switch (pcmd->mCommandId)
  {

    case H264DCD_LLDCMD_INPUTSTREAM_CFG:
    {
      H264DCD_STREAM_DATA_CONFIG data_cfg;

      if(copy_from_user(&data_cfg, (H264DCD_STREAM_DATA_CONFIG *)pcmd->mArg, sizeof(data_cfg)) != 0U)
      {
        ret = -EIO;
      }
      else
      {
        H264dcd_inputstream_cfg(reg_base, &data_cfg);
      }
    }
    break;

    case H264DCD_LLDCMD_FIFO_STATUS_GET:
    {
      H264DCD_STREAM_FIFO_STATUS fifo_st;

      if(copy_from_user(&fifo_st, (H264DCD_STREAM_FIFO_STATUS *)pcmd->mArg, sizeof(fifo_st)) != 0U)
      {
        ret = -EIO;
      }
      else
      {
        H264dcd_fifostatus_get(reg_base, &fifo_st);
        if(copy_to_user((H264DCD_STREAM_FIFO_STATUS *)pcmd->mArg, &fifo_st, sizeof(fifo_st)) != 0U)
        {
            ret = -EIO;
        }
      }
    }
    break;

    case H264DCD_LLDCMD_PCK_STATUS_GET:
    {
      H264DCD_STREAM_DATA_STATUS data_st;

      if(copy_from_user(&data_st, (H264DCD_STREAM_DATA_STATUS *)pcmd->mArg, sizeof(data_st)) != 0U)
      {
        ret = -EIO;
      }
      else
      {
        H264dcd_packetstatus_get(reg_base, &data_st);
        if(copy_to_user((H264DCD_STREAM_DATA_STATUS *)pcmd->mArg, &data_st, sizeof(data_st)) != 0U)
        {
            ret = -EIO;
        }
      }
    }
    break;

    case H264DCD_LLDCMD_FIFO_WATERMARK_SET:
    {
      H264DCD_FIFO_WTM stream_wtm;

      if(copy_from_user(&stream_wtm, (H264DCD_FIFO_WTM *)pcmd->mArg, sizeof(stream_wtm)) != 0U)
      {
        ret = -EIO;
      }
      else
      {
        H264dcd_fifo_wtmklevel_set(reg_base, stream_wtm);
      }
    }
    break;

    case H264DCD_LLDCMD_FIFO_CLEAR:
    {
      H264DCD_STREAM_ID str_no;

      if(copy_from_user(&str_no, (H264DCD_STREAM_ID *)pcmd->mArg, sizeof(str_no)) != 0U)
      {
        ret = -EIO;
      }
      else
      {
        H264dcd_fifo_clear(reg_base, str_no);
      }
    }
    break;

    case H264DCD_LLDCMD_TIMEOUT_SET:
    {
      uint16_t h264_to;

      if(copy_from_user(&h264_to, (uint16_t *)pcmd->mArg, sizeof(h264_to)) != 0U)
      {
        ret = -EIO;
      }
      else
      {
        H264dcd_timeoutset(reg_base, h264_to);
      }
    }
    break;

    case H264DCD_LLDCMD_TIMEOUT_ENABLE:
    {
      H264DCD_TIMEOUT_ENABLE to_enable;

      if(copy_from_user(&to_enable, (H264DCD_TIMEOUT_ENABLE *)pcmd->mArg, sizeof(to_enable)) != 0U)
      {
        ret = -EIO;
      }
      else
      {
        H264dcd_timeouten(reg_base, to_enable);
      }
    }
    break;

    case H264DCD_LLDCMD_SW_RESET:
    {
      H264dcd_swreset(reg_base);
    }
    break;

    case H264DCD_LLDCMD_OUTSTREAM_CFG:
    {
      H264DCD_OUTPUT_BUFFCFG output_cfg;

      if(copy_from_user(&output_cfg, (H264DCD_OUTPUT_BUFFCFG *)pcmd->mArg, sizeof(output_cfg)) != 0U)
      {
        ret = -EIO;
      }
      else
      {
        H264dcd_output_cfg(reg_base, &output_cfg);
      }
    }
    break;

    case H264DCD_LLDCMD_OUTSAMPLEMODE_SET:
    {
      H264DCD_OUTPUT_SAMPLEMODE out_smode;

      if(copy_from_user(&out_smode, (H264DCD_OUTPUT_SAMPLEMODE *)pcmd->mArg, sizeof(out_smode)) != 0U)
      {
        ret = -EIO;
      }
      else
      {
        H264dcd_outsamplemode_set(reg_base, out_smode);
      }
    }
    break;

    case H264DCD_LLDCMD_OUTCOLOURDATA_SET:
    {
      H264DCD_OUTPUT_COLOURDATA out_coldata;

      if(copy_from_user(&out_coldata, (H264DCD_OUTPUT_COLOURDATA *)pcmd->mArg, sizeof(out_coldata)) != 0U)
      {
        ret = -EIO;
      }
      else
      {
        H264dcd_outcolourdata_set(reg_base, &out_coldata);
      }
    }
    break;

    case H264DCD_LLDCMD_DATAFLOWMODE_SET:
    {
      H264DCD_DATAFLOW_MODE data_mode;

      if(copy_from_user(&data_mode, (H264DCD_DATAFLOW_MODE *)pcmd->mArg, sizeof(data_mode)) != 0U)
      {
        ret = -EIO;
      }

      H264dcd_flowmode_set(reg_base, data_mode);
    }
    break;

    case H264DCD_LLDCMD_DATAFLOWMODE_GET:
    {
      H264DCD_DATAFLOW_MODE data_mode;

      H264dcd_flowmode_get(reg_base, &data_mode);

      if(copy_to_user((H264DCD_DATAFLOW_MODE *)pcmd->mArg, &data_mode, sizeof(data_mode)) != 0U)
      {
        ret = -EIO;
      }
    }
    break;

    case H264DCD_LLDCMD_BANKSTRIDE_SET:
    {
      H264DCD_OUTPUT_BKSTRIDE out_bkstride;

      if(copy_from_user(&out_bkstride, (H264DCD_OUTPUT_BKSTRIDE *)pcmd->mArg, sizeof(out_bkstride)) != 0U)
      {
        ret = -EIO;
      }
      else
      {
        H264dcd_bankstride_set(reg_base, out_bkstride);
      }
    }
    break;

    case H264DCD_LLDCMD_BANKSTRIDE_GET:
    {
      H264DCD_OUTPUT_BKSTRIDE out_bkstride;

      H264dcd_bankstride_get(reg_base, &out_bkstride);

      if(copy_to_user((H264DCD_OUTPUT_BKSTRIDE *)pcmd->mArg, &out_bkstride, sizeof(out_bkstride)) != 0U)
      {
        ret = -EIO;
      }
    }
    break;

    case H264DCD_LLDCMD_DCD_CH_STOP:
    {
      H264DCD_CH_CONTROL channel_st;

      if(copy_from_user(&channel_st, (H264DCD_CH_CONTROL *)pcmd->mArg, sizeof(channel_st)) != 0U)
      {
        ret = -EIO;
      }
      else
      {
        H264dcd_dcd_chcontrol(reg_base, channel_st);
      }
    }
    break;

    case H264DCD_LLDCMD_DCD_INFRAMESIZE_SET:
    {
      H264DCD_INFRAME_SIZE image_data;

      if(copy_from_user(&image_data, (H264DCD_INFRAME_SIZE *)pcmd->mArg, sizeof(image_data)) != 0U)
      {
        ret = -EIO;
      }
      else
      {
        H264dcd_dcd_inframesz(reg_base, &image_data);
      }
    }
    break;

    case H264DCD_LLDCMD_DCD_CFG_SET:
    {
        H264DCD_DECOD_CONFIG dcd_config;

        if(copy_from_user(&dcd_config, (H264DCD_DECOD_CONFIG *)pcmd->mArg, sizeof(dcd_config)) != 0U)
        {
          ret = -EIO;
        }
        else
        {
          H264dcd_dcd_cfgset(reg_base, &dcd_config);
        }
    }
    break;

    case H264DCD_LLDCMD_DCD_CFG_GET:
    {
      H264DCD_DECOD_CONFIG dcd_config;

      H264dcd_dcd_cfgget(reg_base, &dcd_config);

      if(copy_to_user((H264DCD_DECOD_CONFIG *)pcmd->mArg, &dcd_config, sizeof(dcd_config)) != 0U)
      {
        ret = -EIO;
      }
    }
    break;

    case H264DCD_LLDCMD_DCD_THRLEVELS_SET:
    {
        H264DCD_DECOD_THRLEVELS dcd_levels;

        if(copy_from_user(&dcd_levels, (H264DCD_DECOD_THRLEVELS *)pcmd->mArg, sizeof(dcd_levels)) != 0U)
        {
          ret = -EIO;
        }
        else
        {
          H264dcd_thrlevels_set(reg_base, &dcd_levels);
        }
    }
    break;

    case H264DCD_LLDCMD_DCD_THRLEVELS_GET:
    {
      H264DCD_DECOD_THRLEVELS dcd_levels;

      H264dcd_thrlevels_get(reg_base, &dcd_levels);

      if(copy_to_user((H264DCD_DECOD_THRLEVELS *)pcmd->mArg, &dcd_levels, sizeof(dcd_levels)) != 0U)
      {
        ret = -EIO;
      }
    }
    break;

    case H264DCD_LLDCMD_DCD_REFMEMORY_SET:
    {
      H264DCD_DECOD_REFMEM refmem_data;

      if(copy_from_user(&refmem_data, (H264DCD_DECOD_REFMEM *)pcmd->mArg, sizeof(refmem_data)) != 0U)
      {
        ret = -EIO;
      }
      else
      {
        H264dcd_refmemaddress_set(reg_base, refmem_data);
      }
    }
    break;

    case H264DCD_LLDCMD_DCD_REFMEMORY_GET:
    {
      H264DCD_DECOD_REFMEM refmem_data;

      if(copy_from_user(&refmem_data, (H264DCD_DECOD_REFMEM *)pcmd->mArg, sizeof(refmem_data)) != 0U)
      {
        ret = -EIO;
      }
      else
      {
        H264dcd_refmemaddress_get(reg_base, &refmem_data);
        if(copy_to_user((H264DCD_DECOD_REFMEM *)pcmd->mArg, &refmem_data, sizeof(refmem_data)) != 0U)
        {
          ret = -EIO;
        }
      }
    }
    break;

    case H264DCD_LLDCMD_CH_STATUS_GET:
    {
      H264DCD_DECOD_CHANNELST ch_data;

      if(copy_from_user(&ch_data, (H264DCD_DECOD_CHANNELST *)pcmd->mArg, sizeof(ch_data)) != 0U)
      {
        ret = -EIO;
      }
      else
      {
        H264dcd_chstatus_get(reg_base, &ch_data);
        if(copy_to_user((H264DCD_DECOD_CHANNELST *)pcmd->mArg, &ch_data, sizeof(ch_data)) != 0U)
        {
          ret = -EIO;
        }
      }
    }
    break;

    case H264DCD_LLDCMD_PICDCD_PARAM_GET:
    {
      H264DCD_PIC_PARAMS picture_par;

      if(copy_from_user(&picture_par, (H264DCD_PIC_PARAMS *)pcmd->mArg, sizeof(picture_par)) != 0U)
      {
        ret = -EIO;
      }
      else
      {
        H264dcd_pictureparam_get(reg_base, &picture_par);
        if(copy_to_user((H264DCD_PIC_PARAMS *)pcmd->mArg, &picture_par, sizeof(picture_par)) != 0U)
        {
          ret = -EIO;
        }
      }
    }
    break;

    case H264DCD_LLDCMD_PICDCD_STATUS_GET:
    {
      H264DCD_PIC_STATUS picture_parst;

      if(copy_from_user(&picture_parst, (H264DCD_PIC_STATUS *)pcmd->mArg, sizeof(picture_parst)) != 0U)
      {
        ret = -EIO;
      }
      else
      {
        H264dcd_picturestatus_get(reg_base, &picture_parst);
        if(copy_to_user((H264DCD_PIC_STATUS *)pcmd->mArg, &picture_parst, sizeof(picture_parst)) != 0U)
        {
            ret = -EIO;
        }
      }
    }
    break;

    case H264DCD_LLDCMD_PICDCD_GENPARAMS_GET:
    {
      H264DCD_PIC_GENPARAMS pic_genprm;

      H264dcd_picgenparams_get(reg_base, &pic_genprm);

      if(copy_to_user((H264DCD_PIC_GENPARAMS *)pcmd->mArg, &pic_genprm, sizeof(pic_genprm)) != 0U)
      {
        ret = -EIO;
      }
    }
    break;

    case H264DCD_LLDCMD_IRQ_CONTROL:
    {
      uint32_t interrupt_mask;

      if(copy_from_user(&interrupt_mask, (uint32_t *)pcmd->mArg, sizeof(interrupt_mask)) != 0U)
      {
        ret = -EIO;
      }
      else
      {
        H264dcd_interrupt_ctrl(reg_base, interrupt_mask);
      }
    }
    break;

    case H264DCD_LLDCMD_IRQ_GET:
    {
      uint32_t intr_mask;

      H264dcd_interrupt_get(reg_base, &intr_mask);

      if(copy_to_user((uint32_t *)pcmd->mArg, &intr_mask, sizeof(intr_mask)) != 0U)
      {
        ret = -EIO;
      }
    }
    break;

    case H264DCD_LLDCMD_IRQ_TIMEOUT_GET:
    {
      H264DCD_IRQ_TIMEOUT irq_to;

      H264dcd_timeoutirq_get(reg_base, &irq_to);

      if(copy_to_user((H264DCD_IRQ_TIMEOUT *)pcmd->mArg, &irq_to,sizeof(irq_to)) != 0U)
      {
        ret = -EIO;
      }
    }
    break;

    case H264DCD_LLDCMD_IRQ_ERROR_GET:
    {
      H264DCD_IRQ_ERROR irq_err;

      H264dcd_errorirq_get(reg_base, &irq_err);

      if(copy_to_user((H264DCD_IRQ_ERROR *)pcmd->mArg, &irq_err, sizeof(irq_err)) != 0U)
      {
        ret = -EIO;
      }
    }
    break;

    case H264DCD_LLDCMD_IRQ_STREAMSTATUS_GET:
    {
      H264DCD_IRQ_STREAM irq_st;

      if(copy_from_user(&irq_st, (H264DCD_IRQ_STREAM *)pcmd->mArg, sizeof(irq_st)) != 0U)
      {
        ret = -EIO;
      }
      else
      {
        H264dcd_streamirq_get(reg_base, &irq_st);
        if(copy_to_user((H264DCD_IRQ_STREAM *)pcmd->mArg, &irq_st, sizeof(irq_st)) != 0U)
        {
            ret = -EIO;
        }
      }
    }
    break;

    default:
        // Nothing to do
        VDB_LOG_WARNING("Nothing to do!\n");
        break;

  } // end from switch (pcmd->mCommandId)

  return ret;
}

/*============================================================================*/
/**
* @brief          The function h264dcd open
* @details        The function opens special file for h264dcd device
*
* @param[in]      inod      struct inode
* @param[in]      pfile     file open
* @return         int
* @api
* @isr
*
* @pre
*
* @post
*
* @note
*/
static int32_t h264dcd_open(struct inode *inod, struct file *pfile)
{
  __TRACE__();

  return 0;
}

/*============================================================================*/
/**
* @brief          The function h264dcd close
* @details        The function closes special file for h264dcd device
*
* @param[in]      inod      struct inode
* @param[in]      pfile     file to close
* @return         int
* @api
* @isr
*
* @pre
*
* @post
*
* @note
*/
static int32_t h264dcd_close(struct inode *inod, struct file *pfile)
{
  __TRACE__();

  return 0;
}

/*============================================================================*/
/**
* @brief          The function h264dcd_write
* @details        The function handles write syscall
*
* @param[in]      pfile     struct file pointer
* @param[in]      pdata     opinter to buffer data
* @param[in]      size      number of bytes in data buffer
* @param[in]      poffset   offset inside data buffer
* @return         int
* @api
* @isr
*
* @pre
*
* @post
*
* @note
*/
static ssize_t h264dcd_write(struct file* pfile,
                             const char*  pdata,
                             size_t       size,
                             loff_t*      poffset)
{
  ssize_t lRet = size;
  if(size == sizeof(OAL_LldCmd_t))
  {
    OAL_LldCmd_t lCmd = {1};
    if(copy_from_user(
         &lCmd,
         pdata,
         size) == 0U)
    {
      int32_t lRes = 0;
      lRes = (ssize_t)h264dcd_lldcmd(&lCmd);
      if(lRes < 0)
      {
        lRet = lRes;
      } // if returned error
    } // if copy from user ok
    else
    {
      lRet = -EIO;
    } // else from if copy from user ok
  } // if command size fits
  else
  {
    lRet = (ssize_t)(-EOPNOTSUPP);
  } // else from if command size fits

  return lRet;
} // FdmaWrite()

/**********************************************************
 * STRUCT operations
 **********************************************************/
static struct file_operations h264dcd_fops = {
  .owner   = THIS_MODULE,
  .open    = h264dcd_open,
  .release = h264dcd_close,
  .write   = h264dcd_write,
};

/*============================================================================*/
/**
* @brief          The function enables clocks for H264 decoder device
* @details        Enables H264DCD, IPG and B clock for H264 decoder device driver
*
* @param[in]      pdev    struct platform device
* @return         int
* @api
* @isr
*
* @pre
*
* @post
*
* @note
*/
static int32_t h264dcd_enable_clocks(struct platform_device * const pdev)
{
  struct clk *h264dcd_clk;
  struct h264dcd_data *h264_data = dev_get_drvdata(&pdev->dev);

  /* H264DCD clock */
  h264dcd_clk = devm_clk_get(&pdev->dev, DEVICE_NAME);
  if (IS_ERR(h264dcd_clk))
  {
    dev_err(&pdev->dev, "could not get \"%s\" clock\n", DEVICE_NAME);
    return -EFAULT;
  }
  if(clk_prepare_enable(h264dcd_clk) != 0U)
  {
    return -EFAULT;
  }

  h264_data->h264dcd_clk = h264dcd_clk;

  /* IPG clock */
  h264dcd_clk = devm_clk_get(&pdev->dev, IPG_CLK);
  if (IS_ERR(h264dcd_clk))
  {
    dev_err(&pdev->dev, "could not get \"%s\" clock\n", IPG_CLK);
    return -EFAULT;
  }

  if(clk_prepare_enable(h264dcd_clk) != 0U)
  {
    return -EFAULT;
  }
  h264_data->ipg_clk = h264dcd_clk;

  /* B clock */
  h264dcd_clk = devm_clk_get(&pdev->dev, B_CLK);
  if (IS_ERR(h264dcd_clk))
  {
    dev_err(&pdev->dev, "could not get \"%s\" clock\n", B_CLK);
    return -EFAULT;
  }

  if(clk_prepare_enable(h264dcd_clk) != 0U)
  {
    return -EFAULT;
  }

  h264_data->b_clk = h264dcd_clk;

  return 0;
}

/*============================================================================*/
/**
* @brief          The function h264dcd dev create
* @details        The function creates and registers h264dcd device
*
* @return         int
* @api
* @isr
*
* @pre
*
* @post
*
* @note
*/
static int32_t h264dcd_dev_create(void)
{
  int32_t ret = 0;

  __TRACE__();

  /* Alloc MAJOR number for the character and
  * the 1st minor device in dev
  */
  ret = alloc_chrdev_region(&h264dcd_devn, 0, 1, DRIVER_NAME);
  if (ret < 0)
  {
    printk(H264DCD_INFO "alloc_region failed: %d\n", ret);
    return ret;
  }

  h264dcd_class = class_create(THIS_MODULE, DRIVER_NAME);
  if (NULL == h264dcd_class)
  {
    printk(H264DCD_INFO "class_create failed %d\n", ret);
    return -1;
  }

  /* Device is created and registered in sysfs */
  if (NULL == (device_create(h264dcd_class, NULL,
        h264dcd_devn, NULL, DEVICE_NAME)))
  {
    printk(H264DCD_INFO "device_create failed %d\n", ret);
    return -1;
  }

  return 0;
}

/*============================================================================*/
/**
* @brief          The function h264dcd probe
* @details        The function h264dcd probe
*
* @param[in]      pdev      struct platform device
* @return         int
* @api
* @isr
*
* @pre
*
* @post
*
* @note
*/
static int32_t h264dcd_probe(struct platform_device *pdev)
{
  struct resource *res;
  struct h264dcd_data *h264_data;

  int32_t ret = 0;

  __TRACE__();

  /* create device and register it in /dev through sysfs */
  ret = h264dcd_dev_create();
  if (ret < 0)
  {
    return -ENODEV;
  }

  /* map register space */
  res = platform_get_resource(pdev, IORESOURCE_MEM, 0U);
  if (NULL == res)
  {
    dev_err(&pdev->dev, "could not get memory IO resource\n");
    return -ENODEV;
  }

  h264_data = devm_kzalloc(&pdev->dev, sizeof(struct h264dcd_data), GFP_KERNEL);
  dev_set_drvdata(&pdev->dev, h264_data);

  /* setup file operations */
  cdev_init(&(h264_data->chdev), &h264dcd_fops);
  ret = cdev_add(&(h264_data->chdev), h264dcd_devn, 1);
  if (ret < 0)
  {
    printk(H264DCD_INFO "cdev_add failed with %d\n", ret);
    return -ENODEV;
  }

  h264dcd_reg_base = devm_ioremap_resource(&pdev->dev, res);
  if (IS_ERR(h264dcd_reg_base))
  {
    dev_err(&pdev->dev, "could not ioremap resource\n");
    return -ENOMEM;
  }

  /* enable clocks for H264 */
  ret = h264dcd_enable_clocks(pdev);
  if (ret < 0)
  {
    return ret;
  }

  pm_runtime_enable(&pdev->dev);
  ret = pm_runtime_get_sync(&pdev->dev);

  __TRACE__();

  return ret;
}

/*============================================================================*/
/**
* @brief          The function h264dcd remove
* @details        The function cleans h264dcd resources
*
* @param[in]      pdev      struct platform device
* @return         int
* @api
* @isr
*
* @pre
*
* @post
*
* @note
*/
static int32_t h264dcd_remove(struct platform_device *pdev)
{
  struct h264dcd_data *h264_data;
  __TRACE__();

  h264_data = dev_get_drvdata(&pdev->dev);

  /* disable clocks */
  clk_disable_unprepare(h264_data->h264dcd_clk);
  clk_disable_unprepare(h264_data->ipg_clk);
  clk_disable_unprepare(h264_data->b_clk);

  cdev_del(&(h264_data->chdev));

  device_destroy(h264dcd_class, h264dcd_devn);
  class_destroy(h264dcd_class);
  unregister_chrdev_region(h264dcd_devn, 1);

  pm_runtime_put_sync(&pdev->dev);
  pm_runtime_disable(&pdev->dev);

  return 0;
}

/**********************************************************
 * DCU Linux DTB query related operations
 **********************************************************/
static struct of_device_id h264dcd_dt_ids[] = {
  {
      .compatible = "fsl,s32v234-h264dcd",
  },
  {}
};

/*============================================================================*/
/**
* @brief          The function h264dcd runtime suspend
* @details        The function h264dcd runtime suspend
*
* @param[in]      dev      struct device
* @return         int
* @api
* @isr
*
* @pre
*
* @post
*
* @note
*/
static int32_t h264dcd_runtime_suspend(struct device *dev)
{
  struct h264dcd_data *h264_data = dev_get_drvdata(dev);

  clk_disable_unprepare(h264_data->h264dcd_clk);
  clk_disable_unprepare(h264_data->ipg_clk);
  clk_disable_unprepare(h264_data->b_clk);

  return 0;
}

/*============================================================================*/
/**
* @brief          The function h264dcd runtime resume
* @details        The function h264dcd runtime resume
*
* @param[in]      dev      struct device
* @return         int
* @api
* @isr
*
* @pre
*
* @post
*
* @note
*/
static int32_t h264dcd_runtime_resume(struct device *dev)
{
  int32_t ret;
  struct h264dcd_data *h264_data = dev_get_drvdata(dev);

  ret = clk_prepare_enable(h264_data->h264dcd_clk);
  if(ret != 0U)
  {
    return ret;
  }

  ret = clk_prepare_enable(h264_data->ipg_clk);
  if(ret != 0U)
  {
    return ret;
  }

  ret = clk_prepare_enable(h264_data->b_clk);
  return ret;
}

static struct dev_pm_ops h264dcd_pm_ops = {
    SET_RUNTIME_PM_OPS(h264dcd_runtime_suspend,
            h264dcd_runtime_resume, NULL)
};

static struct platform_driver h264dcd_driver = {
  .driver = {
      .name = DRIVER_NAME,
      .owner = THIS_MODULE,
      .of_match_table = h264dcd_dt_ids,
      .pm = &h264dcd_pm_ops,
  },
  .probe = h264dcd_probe,
  .remove = h264dcd_remove,
};

module_platform_driver(h264dcd_driver);

MODULE_AUTHOR("Tomescu Cristian Corneliu");
MODULE_DESCRIPTION("Freescale H264 Decoder Driver");
MODULE_LICENSE("GPL");
