##############################################################################
#
# Freescale Confidential Proprietary
#
# Copyright (c) 2014-16 Freescale Semiconductor;
# All Rights Reserved
#
##############################################################################
#
# THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
# OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
# IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
# INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
# STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
# IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
# THE POSSIBILITY OF SUCH DAMAGE.
#
##############################################################################

SDK_ROOT :=  ../../../../..

ARM_LIB =    libcamdrv.a

# library sources
##############################################################################
# libfdmadrv.a
##############################################################################

VPATH += $(SDK_ROOT)/libs/isp/cam_generic/user/src                              

ARM_LIB_SRCS +=                                                             \
        cam_user.cpp                                                        \
        sony_user.cpp                                                       \
        maxim_user.cpp                                                      \
        ov10640_user.cpp                                                    \
        ov10635_user.cpp                                                    \
        tiub964_user.cpp                                                    \
        ov9716_user.cpp                                                     \

ifneq (,$(findstring v234ce,$(ODIR)))
  ARM_INCS +=                                                               \
    -I$(SDK_ROOT)/platform/s32_v234                                         \
    
else
  ARM_INCS +=                                                               \
    -I$(SDK_ROOT)/platform/fpga_vs4                                         \
    
endif

ARM_INCS +=                                                                 \
        -I$(SDK_ROOT)/isp/inc                                               \
        -I$(SDK_ROOT)/include                                               \
	-I$(SDK_ROOT)/libs/utils/sumat/include                              \
	-I$(SDK_ROOT)/libs/utils/oal/user/include                           \
	-I$(SDK_ROOT)/libs/utils/oal/kernel/include                         \
        -I$(SDK_ROOT)/libs/isp/cam_generic/kernel/include                   \
        -I$(SDK_ROOT)/libs/isp/sequencer/kernel/include                     \
        -I$(SDK_ROOT)/libs/isp/viu/kernel/include                           \
        -I$(SDK_ROOT)/libs/isp/viu/user/include                             

ifneq (,$(findstring gnu-linux,$(ODIR)))

ARM_INCS +=                                                                  \
    -I$(SDK_ROOT)/libs/isp/fdma/kernel/include                               \
    
else

ifneq (,$(findstring gnu-sa,$(ODIR)))
    VPATH += $(SDK_ROOT)/libs/isp/cam_generic/kernel/src                    \
    
    ARM_INCS +=                                                             \
       -I$(SDK_ROOT)/libs/isp/sequencer/kernel/include                      \
       -I$(SDK_ROOT)/libs/isp/csi/kernel/include                            \
    
    ARM_LIB_SRCS +=                                                         \
       cam_func.c                                                           \
       sony_func.c                                                          \
       ov10640_func.c                                                       \
      
endif

endif

ARM_CXOPTS += -Wno-unused-parameter

##############################################################################
