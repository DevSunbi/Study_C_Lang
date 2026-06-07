#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#define NUMTHREADS 3
pthread_mutex_t mutexid=PTHREAD_MUTEX_INITIALIZER;
int count = 0;

void cleanup(void *arg)
{
    printf("%s called.\n", (char*)arg);
    free(arg);
    printf("cleanup : free called\n");
}

void* thread_function(void* arg)
{
    int i;
    char* ptr = (char*)malloc(strlen("thread_handler")+1);
    strcpy(ptr, "thread_handler");
    pthread_cleanup_push(cleanup, ptr);

    //pthread_cleanup_push(&cleanup_handler, NULL);

    for(i=0; i<5; i++) {
        pthread_mutex_lock(&mutexid);
        count++;
        printf("count = %d\n", count);
        sleep(1);
        pthread_mutex_unlock(&mutexid);
    }
    pthread_cleanup_pop(0);
    free(ptr);
    //return NULL;
}

int main(void)
{
    pthread_t threads[NUMTHREADS];
    int i;

    for(i=0; i<NUMTHREADS; i++) {
        pthread_create(&threads[i], NULL, thread_function, NULL);
    }
    for(i=0; i<NUMTHREADS; i++) {
        pthread_join(threads[i], NULL);
    }
}