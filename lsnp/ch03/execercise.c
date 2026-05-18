#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_SIZE 1024

int main(int argc, char* argv[])
{
	int fd, length;
	struct stat file;
	char buffer[MAX_SIZE];

	if(argc!=2)
	{
		fprintf(stderr, "Usage : %s filename\n", argv[0]);
		return 1;
	}

	fd=open(argv[1], O_RDONLY);

	if(fd==-1)
	{
		perror("open");
		fprintf(stderr, "File Read Fail\n");
		return 1;
	}

	printf("buffer : ");

	while(1) 
	{
		length=read(fd, buffer, MAX_SIZE-1);
		printf("%s", buffer);
		if(length < MAX_SIZE-1)
			break;
	}
	printf("\n");
	close(fd);
}
