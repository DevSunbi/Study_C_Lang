#include <stdio.h>
#include <sys/utsname.h>
#include <pwd.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"

// Builtin Commad List
BT_TYPE bt_array[]= {
		"hostname", hostname_func,
		"cd", cd_func,
		"pwd", pwd_func,
		NULL, NULL
};

int check_builtin(char **arglist)
{
	int i;

	for(i=0; bt_array[i].cmd; i++)
		if(!strcmp(bt_array[i].cmd, arglist[0])) {
			bt_array[i].bt_func(arglist);	// call the builtin_funcfion
			return 1;
		}
	return 0;
}
// cd dir_name
// cd
// chdir() 
void cd_func(char **arg)
{
	if(arg[1]==NULL) {
		char* homedir = getenv("HOME");
		chdir(homedir);
	} else {
		if(chdir(arg[1])==-1) {
			perror("chdir");
			return;
		}
		printf("success change directory : %s\n", arg[1]);
	}
}

// getcwd()
void pwd_func(char **arg)
{
	char path[1024];

	getcwd(path, 1023);

	printf("pwd: %s\n",path);
}


void hostname_func(char **arg)
{
	struct utsname hostinfo;

	if(uname(&hostinfo)==-1) {
		perror("uname");
		return ;
	}
	printf("hostname : %s\n", hostinfo.nodename);
}
