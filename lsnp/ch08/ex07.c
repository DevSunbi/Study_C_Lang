#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define LOOP_MAX 10

int commonCounter= 0;

void * inc_thread(void *);

sem_t semid;

int main(void)
{

     pthread_t tid1;
     pthread_t tid2;

     if(sem_init(&semid, 0, 1) == -1) {
        perror("sem_init");
        exit(1);
     }

     if ((pthread_create( &tid1, NULL, inc_thread, "thread1")) ||
         (pthread_create( &tid2, NULL, inc_thread, "thread2"))) {
          perror("pthread_create");
          exit (errno);
     }

    pthread_join(tid1, (void **)NULL);
    pthread_join(tid2, (void **)NULL);

     sem_destroy(&semid);

    return 0;
}

void * inc_thread(void *arg)
{
    int loopCount;
    int temp;
    char buffer[80];
    int i;

    for (loopCount = 0; loopCount < LOOP_MAX; loopCount++) {

        if (sem_wait(&semid) == -1) {
            perror("sem_wait");
            exit(1);
        }

        sprintf(buffer, "<%s> Common counter : from %d to ",
                (char*) arg, commonCounter);
        write(1, buffer, strlen(buffer));

        temp = commonCounter;

        for(i = 0; i < 900000; i++);    // delay

        commonCounter = temp + 1;

        sprintf(buffer, "%d\n", commonCounter);
        write(1, buffer, strlen(buffer));

        if (sem_post(&semid) == -1) {
            perror("sem_post");
            exit(1);
        }

        for(i = 0; i < 500000; i++);    // delay
    }

    return NULL;
}