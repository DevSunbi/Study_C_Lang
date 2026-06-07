#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <dlfcn.h>

static void *handle = NULL;
static void (*fptr_led)(char *) = NULL;
static int (*fptr_cds)(void) = NULL;
static void *(*fptr_threshold)(void *) = NULL;

void *threshold_runner(void *arg)
{
    return fptr_threshold(arg);
}

void *led_thread(void *arg)
{
    fptr_led((char *)arg);
    return NULL;
}

void *pr_thread(void *arg)
{
    (void)arg;
    fptr_cds();
    return NULL;
}

int load_library(void)
{
    char *error;

    handle = dlopen("./librpi.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "dlopen error: %s\n", dlerror());
        return -1;
    }

    dlerror();

    fptr_led = (void (*)(char *))dlsym(handle, "led");
    error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "dlsym led error: %s\n", error);
        dlclose(handle);
        return -1;
    }

    fptr_cds = (int (*)(void))dlsym(handle, "cdsControl");
    error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "dlsym cdsControl error: %s\n", error);
        dlclose(handle);
        return -1;
    }

    fptr_threshold = (void *(*)(void *))dlsym(handle, "threshold_thread");
    error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "dlsym threshold_thread error: %s\n", error);
        dlclose(handle);
        return -1;
    }
    return 0;
}

int main(int argc, char **argv)
{
    pthread_t led_tid;
    pthread_t pr_tid;
    pthread_t threshold_tid;

    if (load_library() == -1) {
        return 1;
    }

    if (argc >= 2) {
        if (strcmp(argv[1], "LED") == 0) {
            if (argc != 3) {
                fprintf(stderr, "Usage: %s LED ON|OFF\n", argv[0]);
                dlclose(handle);
                return 1;
            }

            if (pthread_create(&led_tid, NULL, led_thread, argv[2]) != 0) {
                perror("pthread_create LED");
                dlclose(handle);
                return 1;
            }

            pthread_join(led_tid, NULL);
        }
        else if (strcmp(argv[1], "cds") == 0) {
            if (pthread_create(&threshold_tid, NULL, threshold_runner, NULL) != 0) {
                perror("pthread_create threshold");
                dlclose(handle);
                return 1;
            }

            if (pthread_create(&pr_tid, NULL, pr_thread, NULL) != 0) {
                perror("pthread_create cds");
                dlclose(handle);
                return 1;
            }

            pthread_join(pr_tid, NULL);
            pthread_join(threshold_tid, NULL);
        }
        else if (strcmp(argv[1], "both") == 0) {
            if (argc != 3) {
                fprintf(stderr, "Usage: %s both ON|OFF\n", argv[0]);
                dlclose(handle);
                return 1;
            }

            if (pthread_create(&led_tid, NULL, led_thread, argv[2]) != 0) {
                perror("pthread_create LED");
                dlclose(handle);
                return 1;
            }

            if (pthread_create(&pr_tid, NULL, pr_thread, NULL) != 0) {
                perror("pthread_create cds");
                dlclose(handle);
                return 1;
            }

            pthread_join(led_tid, NULL);
            pthread_join(pr_tid, NULL);
        }
        else {
            fprintf(stderr, "unknown command: %s\n", argv[1]);
            fprintf(stderr, "Usage:\n");
            fprintf(stderr, "  %s LED ON|OFF\n", argv[0]);
            fprintf(stderr, "  %s cds\n", argv[0]);
            fprintf(stderr, "  %s both ON|OFF\n", argv[0]);
            dlclose(handle);
            return 1;
        }
    } else {
        int choice;
        char line[128];
        while (1) {
            printf("\n1 LED  2 CDS  3 Threshold  4 Quit\n");
            printf("Select menu: ");
            if (fgets(line, sizeof(line), stdin) == NULL) {
                break;
            }
            if (sscanf(line, "%d", &choice) != 1) {
                printf("Invalid input. Please enter a number between 1 and 4.\n");
                continue;
            }

            if (choice == 1) {
                printf("Enter state (ON/OFF): ");
                char state[64];
                if (fgets(line, sizeof(line), stdin) != NULL) {
                    if (sscanf(line, "%s", state) == 1) {
                        fptr_led(state);
                    }
                }
            }
            else if (choice == 2) {
                printf("Starting CDS monitoring. Press Ctrl+C to stop.\n");
                fptr_cds();
            }
            else if (choice == 3) {
                printf("Starting CDS with Threshold Control. Press Ctrl+C to stop.\n");
                if (pthread_create(&threshold_tid, NULL, threshold_runner, NULL) != 0) {
                    perror("pthread_create threshold");
                    break;
                }
                if (pthread_create(&pr_tid, NULL, pr_thread, NULL) != 0) {
                    perror("pthread_create cds");
                    break;
                }
                pthread_join(pr_tid, NULL);
                pthread_join(threshold_tid, NULL);
            }
            else if (choice == 4) {
                printf("Quitting program.\n");
                break;
            }
            else {
                printf("Invalid choice. Please enter 1, 2, 3, or 4.\n");
            }
        }
    }

    dlclose(handle);
    return 0;
}