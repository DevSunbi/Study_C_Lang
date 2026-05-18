#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>

#define ENTER '\n'

int main(void)
{
    struct termios tbuf, oldtbuf;
    unsigned char ch;
    ssize_t n;

    if (!isatty(STDIN_FILENO)) {
        fprintf(stderr, "stdin is not a terminal\n");
        return 1;
    }

    if (ioctl(STDIN_FILENO, TCGETS, &tbuf) == -1) {
        perror("ioctl TCGETS");
        return 1;
    }

    oldtbuf = tbuf;

    /*
     * ICANON 해제: 한 글자씩 입력 받기
     * ECHO 해제  : 입력한 글자가 화면에 보이지 않게 하기
     */
    tbuf.c_lflag &= ~(ICANON | ECHO);
    tbuf.c_cc[VMIN] = 1;
    tbuf.c_cc[VTIME] = 0;

    if (ioctl(STDIN_FILENO, TCSETSF, &tbuf) == -1) {
        perror("ioctl TCSETSF");
        return 1;
    }

    while ((n = read(STDIN_FILENO, &ch, 1)) == 1) {
        if (ch == ENTER)
            break;

        printf("%02x ", ch);
        fflush(stdout);
    }

    if (n == -1) {
        perror("read");
        ioctl(STDIN_FILENO, TCSETSF, &oldtbuf);
        return 1;
    }

    printf("\n");

    if (ioctl(STDIN_FILENO, TCSETSF, &oldtbuf) == -1) {
        perror("ioctl restore");
        return 1;
    }

    return 0;
}