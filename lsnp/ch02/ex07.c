#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>
#include <time.h>
#include <unistd.h>

int main(void) {
    int i;
    time_t c_time;
    
    clock_t oldtime, newtime;
    struct tms oldtms, newtms;
   
    long ticks = sysconf(_SC_CLK_TCK);

    if((oldtime=times(&oldtms))==-1) {
        perror("old times");
        exit(1);
    }
    for(i=1;i<=99999999;i++)
        time(&c_time);
    if((newtime=times(&newtms))==-1) {
        perror("new times");
        exit(1);
    }
    printf("Real Time : %ld clocks\n", (long)newtime-oldtime);
    printf("Real Time : %.6f s\n", (double) (newtime-oldtime)/ticks);
    printf("User mode Time : %ld clocks\n", (long)newtms.tms_utime-oldtms.tms_utime);
    printf("User mode Time : %.6f s\n", (double)(newtms.tms_utime-oldtms.tms_utime)/ticks);
    printf("System mode Time : %ld clocks\n", (long)newtms.tms_stime-oldtms.tms_stime);
    printf("System mode Time : %.6f s\n", (double)(newtms.tms_stime-oldtms.tms_stime)/ticks);
    printf("Clock Val : %ld\n", ticks);
    return 0;
}
