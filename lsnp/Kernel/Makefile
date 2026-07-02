obj-m := sk2.o
KDIR := /usr/src/linux

# Raspberry Pi 접속 정보
PI_USER := sunbi
PI_HOST := 100.66.20.91
PI_DIR  := /home/sunbi/kernelHome

MODULE := sk2.ko

default:
	${MAKE} ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -C$(KDIR) M=$(shell pwd) modules
clean:
	${MAKE} -C$(KDIR) M=$(shell pwd) clean
send:
	scp $(MODULE) $(PI_USER)@$(PI_HOST):$(PI_DIR)