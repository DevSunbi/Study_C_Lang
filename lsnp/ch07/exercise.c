#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int usr1_count = 0;
int usr2_count = 0;
int interrupted = 0;

void handler(int signo)
{
	if(signo==SIGUSR1) {
		usr1_count++;
	} else if(signo==SIGUSR2) {
		usr2_count++;
	} else if(signo == SIGINT) {
		interrupted = 1;
	}
}

int main(void)
{
	struct sigaction act;
	sigset_t sigset;
	sigset_t wait_mask;
	sigset_t block_all;

	act.sa_handler = handler;
	act.sa_flags=SA_RESTART;
	
	if((sigaction(SIGUSR1, &act, NULL))==-1){
		perror("SIGUSR1");
		exit(1);
	}

	if((sigaction(SIGUSR2, &act, NULL))==-1) {
		perror("SIGUSR2");
		exit(1);
	}

	if (sigaction(SIGINT, &act, NULL) == -1) {
		perror("sigaction SIGINT");
		exit(1);
	}

	wait_mask = block_all;
	sigdelset(&wait_mask, SIGUSR1);
	sigdelset(&wait_mask, SIGUSR2);
	sigdelset(&wait_mask, SIGINT);

	while (!interrupted) {
		sigsuspend(&wait_mask);
	}

	printf("SIGUSR1 count: %d\n", usr1_count);
	printf("SIGUSR2 count: %d\n", usr2_count);

	return 0;
}
