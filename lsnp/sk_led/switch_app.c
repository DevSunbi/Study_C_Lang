#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include "sk_ioctl.h"

#define BUF_SIZE 1024

int fd;
char buf[BUF_SIZE];

void signal_handler(int signo)
{
    printf("Signal is Catched!!!\n");
    if (signo == SIGIO) {
        lseek(fd, 0, SEEK_SET);
        read(fd, buf, 1);
        if (buf[0] == '1')
            printf("LED ON\n");
        else
            printf("LED OFF\n");
    }
}

int main(void)
{
    memset(buf, 0, BUF_SIZE);

    signal(SIGIO, signal_handler);

    fd = open("/dev/buttondevice", O_RDWR);
    if (fd < 0) {
        perror("/dev/buttondevice error");
        exit(-1);
    }

    sprintf(buf, "%d", getpid());
    write(fd, buf, strlen(buf));

    printf("My PID is %d.\n", getpid());

    while(1);

    close(fd);
    return 0;
}