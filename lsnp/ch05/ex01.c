#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char cmd_buf[256];

	printf("------ system() start ------");
	strcpy(cmd_buf, "sleep 3");
	system(cmd_buf);
	strcpy(cmd_buf, "ls");
	system(cmd_buf);
	printf("\n------ system() end ------\n");
	return 0;
}
