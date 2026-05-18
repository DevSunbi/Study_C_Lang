#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void)
{
	pid_t pid;
	int status;

	switch(pid=fork())
	{
		case -1:
			perror("fork");
			break;
		case 0:
			printf("CHILD PROCESS : %d\n", getpid());
			sleep(30);
			system("echo CHILD");
			system("ps -l");
			exit(0);
			break;
		default:
			printf("PARENT PROCESS : %d\n", getpid());
			printf("Return Value of fork : %d\n\n", pid);
			waitpid(pid, &status, 0);
			if(WIFEXITED(status)) {
				printf("Child Process is deaded by exit() \n");
			}
			else if(WIFSIGNALED(status)){
				printf("Child Process is deaded by Signal\n");
			}
			system("echo PARENT");
			system("ps -l");
			break;
	}
	return 0;
}
