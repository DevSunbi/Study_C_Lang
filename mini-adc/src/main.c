#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#include "backend.h"
#include "cli.h"
#include "config.h"
#include "health.h"
#include "logger.h"
#include "proxy.h"

static void handle_signal(int signo)
{
    (void)signo;

    cli_stop();
    health_stop();
    proxy_stop();
}

int main(void)
{
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);
    signal(SIGPIPE, SIG_IGN);

    logger_init();
    backend_init();

    if (health_start() != 0) {
        fprintf(stderr, "failed to start health checker\n");
        return EXIT_FAILURE;
    }

    if (cli_start() != 0) {
        fprintf(stderr, "failed to start cli\n");

        health_stop();
        health_join();

        return EXIT_FAILURE;
    }

    printf("mini-adc started. listen_port=%d\n", LISTEN_PORT);
    printf("logs: %s, %s\n", ACCESS_LOG_PATH, HEALTH_LOG_PATH);

    if (proxy_start(LISTEN_PORT) != 0) {
        fprintf(stderr, "failed to start proxy\n");
    }

    cli_stop();
    health_stop();

    cli_join();
    health_join();

    printf("mini-adc stopped.\n");

    return EXIT_SUCCESS;
}