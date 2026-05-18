#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
	int fd;

	if((fd=open("/etc/hosts", O_RDONLY))==-1){
		perror("open1");
		fprintf(stderr, "File Read Fail\n");
	}
	else{
		printf("File Read Success!! fd=%d\n", fd);
		//close(fd);
	}

	if((fd=open("myhosts",O_WRONLY|O_CREAT|O_TRUNC, 0666))==-1){
		perror("open2");
		fprintf(stderr, "File Create Fail\n");
	}
	else
	{
		printf("File Create Success fd=%d\n", fd);
		close(fd);
	}
	return 0;
}
