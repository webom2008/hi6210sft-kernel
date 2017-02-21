################################################################################

1. How to Build
	- get Toolchain
		From android git server , codesourcery and etc ..
		 - gcc-linaro-arm-linux-gnueabihf-4.7

	- edit Makefile
		edit "CROSS_COMPILE" to right toolchain path(You downloaded).
		  EX)   CROSS_COMPILE= $(android platform directory you download)/android/prebuilts/gcc/linux-x86/arm/gcc-linaro-arm-linux-gnueabihf-4.7/bin/arm-linux-gnueabihf-
          Ex)   CROSS_COMPILE=/usr/local/toolchain/gcc-linaro-arm-linux-gnueabihf-4.7/bin/arm-linux-gnueabihf-          // check the location of toolchain
		  or
		  Ex)	export CROSS_COMPILE=arm-linux-gnueabihf-
		  Ex)	export PATH=$PATH:<toolchain_parent_dir>/gcc-linaro-arm-linux-gnueabihf-4.7/bin

		$ make ARCH=arm hisi_hi6210sft_defconfig
		$ make ARCH=arm zImage

2. Output files
	- Kernel : arch/arm/boot/zImage
	- module : drivers/*/*.ko

3. How to Clean
		$ make ARCH=arm distclean
################################################################################