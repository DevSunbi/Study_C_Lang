#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include "sk_ioctl.h"

int main(void){
    int fd;
    int retn;
    //char buf[100] = {0};

    int flag = 0;

    fd = open("/dev/SK", O_RDWR);
    printf("fd=%d\n", fd);
    
    if(fd < 0) {
        perror("/dev/SK error");
        exit(-1);
    } else {
        printf("SK has been detected\n");
    }

    // retn = write(fd, buf, strlen(buf));
    // printf("\nSize of written data : %d\n", retn);

    // memset(buf, 0, 100);
    // retn = read(fd, buf, 100);
    // buf[retn] = '\0';
    // printf("\ndata:%s\n", buf);

    // //getchar();
    // close(fd);

    int choice;

    printf("1.UP 2.DOWN");

    scanf("%d", &choice);

    if(choice == 1) {
        ioctl(fd, SPEED_UP, 0);
    } else {
        ioctl(fd, SPEED_DOWN, 0);
    }
    close(fd);
    return 0;
}