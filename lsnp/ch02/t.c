#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <string.h>
#include <sys/times.h>

int main(void)
{
    char *homedir;
    char filename[256];
    FILE *fp;

    time_t c_time;
    struct tm *l_time;

    homedir = getenv("HOME");
    if (homedir == NULL) {
        fprintf(stderr, "HOME is NULL\n");
        exit(1);
    }

    printf("HOME = [%s]\n", homedir);

    if (time(&c_time) == (time_t)-1) {
        perror("time");
        exit(1);
    }

    l_time = localtime(&c_time);
    if (l_time == NULL) {
        perror("localtime");
        exit(1);
    }

    snprintf(filename, sizeof(filename), "%s/%04d%02d%02d",
             homedir,
             l_time->tm_year + 1900,
             l_time->tm_mon + 1,
             l_time->tm_mday);

    printf("filename = [%s]\n", filename);

    fp = fopen(filename, "w");
    if (fp == NULL) {
        perror(filename);
        exit(1);
    }

    printf("fopen success\n");

    fprintf(fp, "test data\n");

    if (fclose(fp) == EOF) {
        perror("fclose");
        exit(1);
    }

    printf("saved complete\n");

    return 0;
}
