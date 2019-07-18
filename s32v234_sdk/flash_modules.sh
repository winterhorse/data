#!/bin/sh

cd /home/intesight/sourcecode/bsp19_s32v/s32v_sdk1.3/VisionSDK_S32V2_RTM_1_3_0/s32v234_sdk/libs/apex/drivers/kernel/build-v234ce-gnu-linux-d

make ARCH=arm64 CROSS_COMPILE=/home/intesight/sourcecode/bsp19_s32v/tools/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu- LINUX_S32V234_DIR=/home/intesight/sourcecode/bsp19_s32v/linux_v4.14.34_bsp19.0 clean

make ARCH=arm64 CROSS_COMPILE=/home/intesight/sourcecode/bsp19_s32v/tools/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu- LINUX_S32V234_DIR=/home/intesight/sourcecode/bsp19_s32v/linux_v4.14.34_bsp19.0

cp /home/intesight/sourcecode/bsp19_s32v/s32v_sdk1.3/VisionSDK_S32V2_RTM_1_3_0/s32v234_sdk/libs/apex/drivers/kernel/build-v234ce-gnu-linux-d/apex.ko /home/intesight/sourcecode/bsp19_s32v/modules

cd /home/intesight/sourcecode/bsp19_s32v/s32v_sdk1.3/VisionSDK_S32V2_RTM_1_3_0/s32v234_sdk/libs/utils/oal/kernel/build-v234ce-gnu-linux-o

make ARCH=arm64 CROSS_COMPILE=/home/intesight/sourcecode/bsp19_s32v/tools/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu- LINUX_S32V234_DIR=/home/intesight/sourcecode/bsp19_s32v/linux_v4.14.34_bsp19.0 clean

make ARCH=arm64 CROSS_COMPILE=/home/intesight/sourcecode/bsp19_s32v/tools/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu- LINUX_S32V234_DIR=/home/intesight/sourcecode/bsp19_s32v/linux_v4.14.34_bsp19.0

cp /home/intesight/sourcecode/bsp19_s32v/s32v_sdk1.3/VisionSDK_S32V2_RTM_1_3_0/s32v234_sdk/libs/utils/oal/kernel/build-v234ce-gnu-linux-o/oal_cma.ko /home/intesight/sourcecode/bsp19_s32v/modules

cd /home/intesight/sourcecode/bsp19_s32v/s32v_sdk1.3/VisionSDK_S32V2_RTM_1_3_0/s32v234_sdk/libs/isp/csi/kernel/build-v234ce-gnu-linux-d

make ARCH=arm64 CROSS_COMPILE=/home/intesight/sourcecode/bsp19_s32v/tools/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu- LINUX_S32V234_DIR=/home/intesight/sourcecode/bsp19_s32v/linux_v4.14.34_bsp19.0 clean

make ARCH=arm64 CROSS_COMPILE=/home/intesight/sourcecode/bsp19_s32v/tools/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu- LINUX_S32V234_DIR=/home/intesight/sourcecode/bsp19_s32v/linux_v4.14.34_bsp19.0

cp /home/intesight/sourcecode/bsp19_s32v/s32v_sdk1.3/VisionSDK_S32V2_RTM_1_3_0/s32v234_sdk/libs/isp/csi/kernel/build-v234ce-gnu-linux-d/csi.ko /home/intesight/sourcecode/bsp19_s32v/modules

cd /home/intesight/sourcecode/bsp19_s32v/s32v_sdk1.3/VisionSDK_S32V2_RTM_1_3_0/s32v234_sdk/libs/isp/cam_generic/kernel/build-v234ce-gnu-linux-d

make ARCH=arm64 CROSS_COMPILE=/home/intesight/sourcecode/bsp19_s32v/tools/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu- LINUX_S32V234_DIR=/home/intesight/sourcecode/bsp19_s32v/linux_v4.14.34_bsp19.0 clean

make ARCH=arm64 CROSS_COMPILE=/home/intesight/sourcecode/bsp19_s32v/tools/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu- LINUX_S32V234_DIR=/home/intesight/sourcecode/bsp19_s32v/linux_v4.14.34_bsp19.0

cp /home/intesight/sourcecode/bsp19_s32v/s32v_sdk1.3/VisionSDK_S32V2_RTM_1_3_0/s32v234_sdk/libs/isp/cam_generic/kernel/build-v234ce-gnu-linux-d/cam.ko /home/intesight/sourcecode/bsp19_s32v/modules

cd /home/intesight/sourcecode/bsp19_s32v/s32v_sdk1.3/VisionSDK_S32V2_RTM_1_3_0/s32v234_sdk/libs/isp/sequencer/kernel/build-v234ce-gnu-linux-d

make ARCH=arm64 CROSS_COMPILE=/home/intesight/sourcecode/bsp19_s32v/tools/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu- LINUX_S32V234_DIR=/home/intesight/sourcecode/bsp19_s32v/linux_v4.14.34_bsp19.0 clean

make ARCH=arm64 CROSS_COMPILE=/home/intesight/sourcecode/bsp19_s32v/tools/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu- LINUX_S32V234_DIR=/home/intesight/sourcecode/bsp19_s32v/linux_v4.14.34_bsp19.0

cp /home/intesight/sourcecode/bsp19_s32v/s32v_sdk1.3/VisionSDK_S32V2_RTM_1_3_0/s32v234_sdk/libs/isp/sequencer/kernel/build-v234ce-gnu-linux-d/seq.ko /home/intesight/sourcecode/bsp19_s32v/modules

cd /home/intesight/sourcecode/bsp19_s32v/s32v_sdk1.3/VisionSDK_S32V2_RTM_1_3_0/s32v234_sdk/libs/isp/fdma/kernel/build-v234ce-gnu-linux-d

make ARCH=arm64 CROSS_COMPILE=/home/intesight/sourcecode/bsp19_s32v/tools/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu- LINUX_S32V234_DIR=/home/intesight/sourcecode/bsp19_s32v/linux_v4.14.34_bsp19.0 clean

make ARCH=arm64 CROSS_COMPILE=/home/intesight/sourcecode/bsp19_s32v/tools/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu- LINUX_S32V234_DIR=/home/intesight/sourcecode/bsp19_s32v/linux_v4.14.34_bsp19.0

cp /home/intesight/sourcecode/bsp19_s32v/s32v_sdk1.3/VisionSDK_S32V2_RTM_1_3_0/s32v234_sdk/libs/isp/fdma/kernel/build-v234ce-gnu-linux-d/fdma.ko /home/intesight/sourcecode/bsp19_s32v/modules

cd /home/intesight/sourcecode/bsp19_s32v/s32v_sdk1.3/VisionSDK_S32V2_RTM_1_3_0/s32v234_sdk/libs/isp/h264enc/kernel/build-v234ce-gnu-linux-d

make ARCH=arm64 CROSS_COMPILE=/home/intesight/sourcecode/bsp19_s32v/tools/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu- LINUX_S32V234_DIR=/home/intesight/sourcecode/bsp19_s32v/linux_v4.14.34_bsp19.0 clean

make ARCH=arm64 CROSS_COMPILE=/home/intesight/sourcecode/bsp19_s32v/tools/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu- LINUX_S32V234_DIR=/home/intesight/sourcecode/bsp19_s32v/linux_v4.14.34_bsp19.0

cp /home/intesight/sourcecode/bsp19_s32v/s32v_sdk1.3/VisionSDK_S32V2_RTM_1_3_0/s32v234_sdk/libs/isp/h264enc/kernel/build-v234ce-gnu-linux-d/h264enc.ko /home/intesight/sourcecode/bsp19_s32v/modules

cd /home/intesight/sourcecode/bsp19_s32v/s32v_sdk1.3/VisionSDK_S32V2_RTM_1_3_0/s32v234_sdk/libs/isp/sram/kernel/build-v234ce-gnu-linux-d

make ARCH=arm64 CROSS_COMPILE=/home/intesight/sourcecode/bsp19_s32v/tools/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu- LINUX_S32V234_DIR=/home/intesight/sourcecode/bsp19_s32v/linux_v4.14.34_bsp19.0 clean

make ARCH=arm64 CROSS_COMPILE=/home/intesight/sourcecode/bsp19_s32v/tools/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu- LINUX_S32V234_DIR=/home/intesight/sourcecode/bsp19_s32v/linux_v4.14.34_bsp19.0

cp /home/intesight/sourcecode/bsp19_s32v/s32v_sdk1.3/VisionSDK_S32V2_RTM_1_3_0/s32v234_sdk/libs/isp/sram/kernel/build-v234ce-gnu-linux-d/sram.ko /home/intesight/sourcecode/bsp19_s32v/modules


cd /home/intesight/sourcecode/bsp19_s32v/s32v_sdk1.3/VisionSDK_S32V2_RTM_1_3_0/s32v234_sdk/libs/isp/h264dec/kernel/build-v234ce-gnu-linux-d

make ARCH=arm64 CROSS_COMPILE=/home/intesight/sourcecode/bsp19_s32v/tools/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu- LINUX_S32V234_DIR=/home/intesight/sourcecode/bsp19_s32v/linux_v4.14.34_bsp19.0 clean

make ARCH=arm64 CROSS_COMPILE=/home/intesight/sourcecode/bsp19_s32v/tools/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu- LINUX_S32V234_DIR=/home/intesight/sourcecode/bsp19_s32v/linux_v4.14.34_bsp19.0

cp /home/intesight/sourcecode/bsp19_s32v/s32v_sdk1.3/VisionSDK_S32V2_RTM_1_3_0/s32v234_sdk/libs/isp/h264dec/kernel/build-v234ce-gnu-linux-d/h264dcd.ko /home/intesight/sourcecode/bsp19_s32v/modules

cd /home/intesight/sourcecode/bsp19_s32v/s32v_sdk1.3/VisionSDK_S32V2_RTM_1_3_0/s32v234_sdk/libs/isp/jpegdec/kernel/build-v234ce-gnu-linux-d

make ARCH=arm64 CROSS_COMPILE=/home/intesight/sourcecode/bsp19_s32v/tools/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu- LINUX_S32V234_DIR=/home/intesight/sourcecode/bsp19_s32v/linux_v4.14.34_bsp19.0 clean

make ARCH=arm64 CROSS_COMPILE=/home/intesight/sourcecode/bsp19_s32v/tools/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu- LINUX_S32V234_DIR=/home/intesight/sourcecode/bsp19_s32v/linux_v4.14.34_bsp19.0

cp /home/intesight/sourcecode/bsp19_s32v/s32v_sdk1.3/VisionSDK_S32V2_RTM_1_3_0/s32v234_sdk/libs/isp/jpegdec/kernel/build-v234ce-gnu-linux-d/jpegdcd.ko /home/intesight/sourcecode/bsp19_s32v/modules

cd /home/intesight/sourcecode/bsp19_s32v/s32v_sdk1.3/VisionSDK_S32V2_RTM_1_3_0/s32v234_sdk/libs/isp/viu/kernel/build-v234ce-gnu-linux-d

make ARCH=arm64 CROSS_COMPILE=/home/intesight/sourcecode/bsp19_s32v/tools/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu- LINUX_S32V234_DIR=/home/intesight/sourcecode/bsp19_s32v/linux_v4.14.34_bsp19.0 clean

make ARCH=arm64 CROSS_COMPILE=/home/intesight/sourcecode/bsp19_s32v/tools/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu- LINUX_S32V234_DIR=/home/intesight/sourcecode/bsp19_s32v/linux_v4.14.34_bsp19.0

cp /home/intesight/sourcecode/bsp19_s32v/s32v_sdk1.3/VisionSDK_S32V2_RTM_1_3_0/s32v234_sdk/libs/isp/viu/kernel/build-v234ce-gnu-linux-d/viulite.ko /home/intesight/sourcecode/bsp19_s32v/modules

cd /home/intesight/sourcecode/bsp19_s32v/s32v_sdk1.3/VisionSDK_S32V2_RTM_1_3_0/s32v234_sdk/libs/io/Galcore

./build.sh KERNEL_DIR=/home/intesight/sourcecode/bsp19_s32v/linux_v4.14.34_bsp19.0 TOOLCHAIN=/home/intesight/sourcecode/bsp19_s32v/tools/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu clean

./build.sh KERNEL_DIR=/home/intesight/sourcecode/bsp19_s32v/linux_v4.14.34_bsp19.0 TOOLCHAIN=/home/intesight/sourcecode/bsp19_s32v/tools/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu

cp /home/intesight/sourcecode/bsp19_s32v/s32v_sdk1.3/VisionSDK_S32V2_RTM_1_3_0/s32v234_sdk/libs/io/Galcore/galcore.ko /home/intesight/sourcecode/bsp19_s32v/modules

