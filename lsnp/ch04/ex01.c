#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[])
{
   char buffer[1024];
   int fd, n;

   if(argc!=2) {
       fprintf(stderr, "Usage : ex01 device_filename\n");
       exit(1);
   }

   if((fd=open(argv[1],O_RDWR))==-1) {
       perror("open");
       exit(1);
   }
   strcpy(buffer, "Hello, Terminal\n");
   n=strlen(buffer);
   write(fd,buffer,n);

   close(fd);
   return 0;
}