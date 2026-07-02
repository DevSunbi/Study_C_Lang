obj-m := alarm_device.o
KDIR := /usr/src/linux

# Raspberry Pi 접속 정보 (사용자 정보에 맞춰 수정 필요)
PI_USER := sunbi
PI_HOST := 100.66.20.91
PI_DIR  := /home/sunbi/kernelHome

default:
	${MAKE} ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -C$(KDIR) M=$(shell pwd) modules
clean:
	${MAKE} -C$(KDIR) M=$(shell pwd) clean
send:
	scp alarm_device.ko $(PI_USER)@$(PI_HOST):$(PI_DIR)
