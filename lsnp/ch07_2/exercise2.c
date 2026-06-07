#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	int msgid, n;
	char buf[1024];
	struct mymsgbuf {
		long m_type;
		char m_str[1024];
	} sendbuf, recvbuf;

	if((msgid=msgget(0x123400, IPC_CREAT|0666))==-1)
	{
		perror("msgget");
		exit(1);
	}
	
	while(1)
	{
		n=msgrcv(msgid, &recvbuf, 1024, 1, 0);
		recvbuf.m_str[n]='\0';
		printf(">> %s\n", recvbuf.m_str);
		printf(" Input --> ");
		fgets(buf, 1023, stdin);
		
		sendbuf.m_type=2;
		strcpy(sendbuf.m_str, buf);
		msgsnd(msgid, &sendbuf, strlen(sendbuf.m_str),0);
		if(!strncmp(recvbuf.m_str, "end", 3))
			break;
	}

	msgctl(msgid, IPC_RMID, 0);
	return 0;
}
