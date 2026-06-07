#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>

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
