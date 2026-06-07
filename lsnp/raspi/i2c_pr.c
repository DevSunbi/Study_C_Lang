#include <stdio.h>
#include <pthread.h>

extern int threshold;
extern pthread_mutex_t threshold_mutex;

void *threshold_thread(void *arg)
{
    (void)arg;

    int value;
    char line[128];

    while (1) {
        printf("\nEnter new threshold value:\n");

        if (fgets(line, sizeof(line), stdin) == NULL) {
            fprintf(stderr, "input error\n");
            continue;
        }

        if (sscanf(line, "%d", &value) != 1) {
            fprintf(stderr, "invalid input\n");
            continue;
        }

        pthread_mutex_lock(&threshold_mutex);
        threshold = value;
        pthread_mutex_unlock(&threshold_mutex);

        printf("threshold changed to %d\n", value);
    }

    return NULL;
}