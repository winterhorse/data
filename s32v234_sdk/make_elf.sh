#!/bin/sh

cd /home/intesight/sourcecode/bsp19_s32v/s32v_sdk1.3/VisionSDK_S32V2_RTM_1_3_0/s32v234_sdk/demos/isp/max9286_96705_4channel_uyvy/build-v234ce-gnu-linux-o

make cleansub

export ARCH=arm64

export CROSS_COMPILE=aarch64-linux-gnu-

export LINUX_S32V234_DIR=/home/intesight/sourcecode/bsp19_s32v/linux_v4.14.34_bsp19.0

#export APU_TOOLS=/home/intesight/sourcecode/bsp20/s32v_bsp20/s32v_sdk1.3/VisionSDK_S32V2_RTM_1_3_0/apex-llvm/APU_Compiler_v1.0_b530.bin

export PATH=/home/intesight/sourcecode/bsp19_s32v/s32v_sdk1.3/VisionSDK_S32V2_RTM_1_3_0/compilers/gcc-6.3.1-linaro-Earmv7-eabi/i686-linux/bin:$PATH

export PATH=/home/intesight/sourcecode/bsp19_s32v/tools/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin:$PATH

make APU_COMP=nxp allsub

cp /home/intesight/sourcecode/bsp19_s32v/s32v_sdk1.3/VisionSDK_S32V2_RTM_1_3_0/s32v234_sdk/demos/isp/max9286_96705_4channel_uyvy/build-v234ce-gnu-linux-o/max9286_96705_4channel_uyvy.elf /home/intesight/sourcecode/bsp19_s32v/modules
