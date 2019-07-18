##############################################################################
#
#  Freescale Semiconductor, Inc.
#  (c) Copyright 2011, Freescale Semiconductor, Inc.
#  Copyright 2017 NXP;
#  ALL RIGHTS RESERVED.
#
##############################################################################
#
#  CONTENT
#
#
#  AUTHOR
#    Rostislav Hulik
#    Mihail Marian Nistor
#
#  DATE
#    2017-03-24
#
#  LANGUAGE
#    make
#
##############################################################################

include $(SDK_ROOT)/build/nbuild/toolchains/aarch64-sa-gnu.mk

C0_CCOPTS += \
  -O3

C0_CXOPTS += \
  -O3

C0_PROMPT := arm64/sa/optimized

include $(SDK_ROOT)/build/nbuild/.C0.mk
