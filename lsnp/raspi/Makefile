CC = aarch64-linux-gnu-gcc
LDLIBS = -lwiringPi -lcrypt

PI_USER := sunbi
PI_HOST := 100.66.20.91
PI_DIR := /home/$(PI_USER)/projectHome

all : main

%.o : %.c
	$(CC) -c -fPIC $<

librpi.so : led.o wiringlight.o rpi_common.o i2c_pr.o
	$(CC) -shared -o $@ $^ $(LDLIBS)
main : main.o librpi.so
	$(CC) main.c -o main -ldl
clean :
	rm -f *.o *.so main

send :
	scp $(FILE) $(PI_USER)@$(PI_HOST):$(PI_DIR)/
