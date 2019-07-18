##############################################################################
#
# Freescale Confidential Proprietary
#
# Copyright (c) 2016 Freescale Semiconductor;
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

SDK_ROOT := ../../../..

APU_LIB = statistics_kernels.a

##############################################################################
# APU Kernel library built (code for APU - kernel implementation)
##############################################################################

APU_INCS +=                                                                  \
    -I./                                                                     \
    -I$(SDK_ROOT)/include

APU_LIB_SRCS +=                                                              \
    histogram_acf.cpp                                                        \
    histogram_apu.cpp                                                   \
    column_sum_acf.cpp                                                       \
    column_sum_apu.cpp                                                  \
    histofgrad_acf.cpp                                                       \
    histofgrad_apu.cpp                                                  \
    reduction_acf.cpp                                                        \
    reduction_apu.cpp                                                   \
    reduction_for_clmn_acf.cpp                                               \
    reduction_for_clmn_apu.cpp                                          \
    accumulation_acf.cpp                                              \
    accumulation_apu.cpp                                         \

APU_DEFS += -DACF_KERNEL_IMPLEMENTATION

X86_INCS += -I$(SDK_ROOT)/include

ifeq (,$(findstring -nxp,$(ODIR)))
  APU_CCOPTS += +W noodle,-Wnone
  APU_CXOPTS += +W noodle,-Wnone
endif

##############################################################################
# Kernel db generator - builds an exe application and generates .h header with
#                       kernel description
# Do not change following code
##############################################################################

X86_LIB 	 =	$(addsuffix acf.a,$(basename $(APU_LIB)))
X86_LIB_SRCS =	$(APU_LIB_SRCS)
X86_KERNEL_DB = "on"

##############################################################################

