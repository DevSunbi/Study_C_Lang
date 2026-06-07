#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void child_handler(int signo);


int main(void)
{
	struct sigaction act;

	act.sa_handler=child_handler;
	sigfillset(&act.sa_mask);
	act.sa_flags=SA_RESTART;
	sigaction(SIGCHLD, &act, NULL);
 
	switch(fork()) {
		case -1:
			perror("fork");
			exit(1);
			break;
		case 0:
			printf("CHILD 1 : %d\n", getpid());
			execlp("sleep", "sleep", "20", NULL);
			perror("child1");
			exit(1);
			break;
		default:
			switch(fork()) {
				case -1:
					perror("fork");
					exit(1);
					break;
				case 0:
					printf("CHILD 2 : %d\n", getpid());
					execlp("sleep", "sleep", "30", NULL);
					perror("child2");
					exit(1);
					break;
				default:
					printf("PARENT : %d\n", getpid());
					break;
			}
	}
	while(1);
	return 0;
}

void child_handler(int signo) 
{
	pid_t  pid;

  	for (;;) { 
		pid = waitpid(-1, NULL, WNOHANG);
		if (pid == 0) { 		 
      			break;
		} else if (pid == -1 && errno == ECHILD) {  
      			break;

   		} else if (pid == -1) {	 
      			perror("waitpid");
      			abort();
    		}
		printf("PID of the dead child = %d\n", pid);

  	}
  	return;
}
