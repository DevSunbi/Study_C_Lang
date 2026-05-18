#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "minishell.h"

#define MAXLINE 255

int main(void) {
    char line[MAXLINE];
    char** arglist;

    fputs("myshell> ",stdout);

    while (fgets(line,MAXLINE,stdin)) {
        if(!strncmp(line,"exit",4))
            exit(0);
//        fputs(line, stdout);
	if((arglist=command_parse(line))!=NULL) {
		if(!check_builtin(arglist))
			for(int i=0; arglist[i]; i++)
				printf("%s\n", arglist[i]);
		}
	fputs("myshell> ", stdout);
	command_freelist(arglist);
    }
    return 0;
}
