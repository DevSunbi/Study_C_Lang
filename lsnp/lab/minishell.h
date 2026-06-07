char** command_parse(char*);
void command_freelist(char **);
int check_builtin(char**);
void hostname_func(char**);
void cd_func(char**arg);
void pwd_func(char**arg);
void is_excutable(char ** );
void child_handler(int signo);
int find_pipe(char **);

typedef struct{
	char *cmd;
	void (*bt_func)(char**);
}BT_TYPE;

