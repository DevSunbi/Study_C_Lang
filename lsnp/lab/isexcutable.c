#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include "minishell.h"

int is_redirect(char **arglist)
{
    int i;
    int fd;
    int redirect_index = -1;

    for(i=0; arglist[i]!=NULL; i++) {
        if(strcmp(arglist[i], ">") == 0) {
            if(redirect_index != -1) {
                fprintf(stderr, "multiple redirection operators\n");
                return -1;
            }
            redirect_index = i;
        }
    }

    if(redirect_index == -1){
        return 0;
    }

    if(arglist[redirect_index + 1] == NULL) {
        fprintf(stderr, "syntax error : expextred filename after '>'\n");
        return -1;
    }

    if(arglist[redirect_index + 2] != NULL) {
        fprintf(stderr, "syntax error : too many arguments after output file\n");
        return -1;
    }

    fd = open(arglist[redirect_index + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if(fd==-1) {
        perror("open");
        return -1;
    }

    if(dup2(fd, STDOUT_FILENO) == -1 ) {
        perror("dup2");
        close(fd);
        return -1;
    }

    close(fd);

    arglist[redirect_index] = NULL;

    return 0;

}

int find_pipe(char **arglist)
{
	int i = 0;
	
	while(arglist[i] != NULL) {
		if(strcmp(arglist[i], "|") == 0) {
			return i;
		}
		i++;
	}
	return -1;
}

int is_background(char** arglist)
{
	int i;

	for(i=0; arglist[i]!=NULL;i++);

	if(!strcmp(arglist[i-1], "&")) {
		arglist[i-1]=NULL;
		return 1;
	}
	return 0;
}

void is_excutable(char **arglist)
{
    pid_t pid, pid1, pid2;
    int pd[2];
    int pipe_index;
    int backflag;

    if (arglist == NULL || arglist[0] == NULL) {
        return;
    }

    backflag = is_background(arglist);

    pipe_index = find_pipe(arglist);

    if (pipe_index != -1) {
        if (pipe_index == 0 || arglist[pipe_index + 1] == NULL) {
            fprintf(stderr, "pipe syntax error\n");
            return;
        }

        arglist[pipe_index] = NULL;

        char **left_cmd = arglist;
        char **right_cmd = &arglist[pipe_index + 1];

        if (pipe(pd) == -1) {
            perror("pipe");
            return;
        }

        pid1 = fork();

        if (pid1 == -1) {
            perror("fork");
            close(pd[0]);
            close(pd[1]);
            return;
        }

        if (pid1 == 0) {
            signal(SIGINT, SIG_DFL);

            close(pd[0]);

            if (dup2(pd[1], STDOUT_FILENO) == -1) {
                perror("dup2");
                exit(1);
            }

            close(pd[1]);

            execvp(left_cmd[0], left_cmd);
            perror("execvp left");
            exit(127);
        }

        pid2 = fork();

        if (pid2 == -1) {
            perror("fork");
            close(pd[0]);
            close(pd[1]);
            waitpid(pid1, NULL, 0);
            return;
        }

        if (pid2 == 0) {
            signal(SIGINT, SIG_DFL);

            close(pd[1]);

            if (dup2(pd[0], STDIN_FILENO) == -1) {
                perror("dup2");
                exit(1);
            }

            close(pd[0]);

            if(is_redirect(right_cmd) == -1) {
                exit(1);
            }

            execvp(right_cmd[0], right_cmd);
            perror("execvp right");
            exit(127);
        }

        close(pd[0]);
        close(pd[1]);

        if (backflag) {
            printf("[background pid] %d %d\n", pid1, pid2);
        } else {
            waitpid(pid1, NULL, 0);
            waitpid(pid2, NULL, 0);
        }

        return;
    }

    pid = fork();
    
    switch (pid) {
    case -1:
        perror("fork()");
        exit(1);

    case 0:
        signal(SIGINT, SIG_DFL);

        if(is_redirect(arglist) == -1) {
            exit(1);
        }

        execvp(arglist[0], arglist);
        perror("execvp");
        exit(127);

    default:
        if (backflag) {
            printf("[background pid] %d\n", pid);
        } else {
            waitpid(pid, NULL, 0);
        }
        break;
    }
}