#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include "sk_ioctl.h"

#define BUF_SIZE 1024

int fd_btn_reg;
int fd_led, fd_buz;
char pidbuf[32];

volatile sig_atomic_t sigio_flag = 0;

char buf[BUF_SIZE];

void signal_handler(int signo)
{
    if (signo == SIGIO) {
        sigio_flag = 1;
    }
}

int read_button_value(void)  {
    int fd_read;
    char ch;
    ssize_t n;

    fd_read = open("/dev/buttondevice", O_RDONLY);

    if(fd_read < 0) {
        perror("open /dev/buttondevice for read");
        return -1;
    }

    n = read(fd_read, &ch, 1);
    if( n < 0 ) {
        perror("read button error");
        close(fd_read);
        return -1;
    }

    if(n==0) {
        printf("read returned 0 byte\n");
        close(fd_read);
        return -1;
    }

    close(fd_read);
    if(write(fd_btn_reg, pidbuf, strlen(pidbuf)) < 0) {
        perror("re-register button error");
        return -1;
    }

    return ch;
}

int main(void)
{
    char buf[BUF_SIZE];
    ssize_t n;
    int value;

    memset(buf, 0, BUF_SIZE);

    signal(SIGIO, signal_handler);

    fd_btn_reg = open("/dev/buttondevice", O_RDWR);
    if (fd_btn_reg < 0) {
        perror("/dev/buttondevice error");
        exit(1);
    }

    fd_led = open("/dev/LED", O_RDWR);
    if(fd_led < 0) {
        perror("/dev/LED open error");
        close(fd_btn_reg);
        exit(1);
    }

    fd_buz = open("/dev/BZdevice", O_RDWR);
    if (fd_buz < 0) {
        perror("/dev/BZdevice open error");
        close(fd_led);
        close(fd_btn_reg);
        exit(1);
    }

    snprintf(pidbuf, sizeof(pidbuf), "%d", getpid());

    if(write(fd_btn_reg, pidbuf, strlen(pidbuf)) < 0) {
        perror("write PID to buttondevice error");
        close(fd_led);
        close(fd_btn_reg);
        exit(1);
    }

    printf("My PID is %d.\n", getpid());

    while(1) {
        if(sigio_flag) {
            sigio_flag = 0;

            value = read_button_value();

            if (value == '0') {
                printf("Button Released (0) -> LED OFF\n");
                write(fd_led, "0", 1);
                write(fd_buz, "0", 1);
            } else if (value == '1') {
                printf("Button Pressed (1) -> LED ON\n");
                write(fd_led, "1", 1);
                write(fd_buz, "1", 1);
            } else {
                printf("Unknown button value: %d\n", value);
            }
        }
    }

    close(fd_buz);
    close(fd_led);
    close(fd_btn_reg);
    return 0;
}