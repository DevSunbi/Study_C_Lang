#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
   int fd;
   char buf[256];

   if((fd=open("myhosts",O_RDONLY))==-1)
   {
       perror("open");
       exit(1);
   }
   lseek(fd, 10L, SEEK_SET);
   read(fd, buf, 10);
   buf[10]='\0';
   printf("SEEK_SET : %s\n", buf);
   printf("----------------------------\n\n");

   lseek(fd, 10L, SEEK_CUR);
   read(fd, buf, 10);
   buf[10]='\0';
   printf("SEEK_CUR : %s\n", buf);
   printf("----------------------------\n\n");

   lseek(fd, -10L, SEEK_END);
   read(fd, buf, 10);
   buf[10]='\0';
   printf("SEEK_END : %s\n", buf);
   close(fd);

   return 0;
}
