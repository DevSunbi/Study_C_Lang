#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include "minishell.h"

#define MAXLINE 255

int main(void) {
	char line[MAXLINE];
	char** arglist;

	signal(SIGINT, SIG_IGN);
	
	struct sigaction act;
	act.sa_handler = child_handler;
	sigfillset(&act.sa_mask);
	act.sa_flags = SA_RESTART;

	sigaction(SIGCHLD, &act, NULL);

	fputs("minishell> ",stdout);

	while (fgets(line,MAXLINE,stdin)) {
		if(!strncmp(line,"exit",4))
			exit(0);
		
		if((arglist=command_parse(line))!=NULL){
			if(!check_builtin(arglist)){	
				//for (int i = 0; arglist[i] != NULL; i++) 
				//	printf("%s\n",arglist[i]);
				is_excutable(arglist);	// 외부 명령의 경우
			}
		}
	fputs("minishell> ",stdout);
	command_freelist(arglist);
	}
	return 0;
}
