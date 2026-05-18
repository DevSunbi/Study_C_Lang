#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>

int main(void)
{
    time_t cur_time;
    struct timeval cur_gettimeofday;
    
    time(&cur_time);
    printf("time : current seconds = %ld\n", (long)cur_time);
    
    gettimeofday(&cur_gettimeofday, NULL);
    printf("current seconds = %ld, micro seconds = %ld\n", 
		    (long)cur_gettimeofday.tv_sec, (long)cur_gettimeofday.tv_usec);
    return 0;
}
