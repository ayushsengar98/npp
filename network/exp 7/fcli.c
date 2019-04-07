#include<sys/socket.h>
#include<sys/types.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netdb.h>
#include<netinet/in.h>
#include<string.h>
int main(int argc,char *argv[])
{
	int sd,cd;
	struct sockaddr_in servaddr,cliaddr;
	socklen_t servlen,clilen;
	char buff[1000],buff1[1000];
	pid_t cpid;
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr(argv[1]);
	servaddr.sin_port=htons(5500);
	sd=socket(AF_INET,SOCK_STREAM,0);
	cd=connect(sd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	cpid=fork();
	if(cpid==0)
	{
		while(1)
		{
			bzero(&buff,sizeof(buff));
			printf("%s\n","Enter the input data:");
			fgets(buff,10000,stdin);
			send(sd,buff,strlen(buff)+1,0);
			printf("%s\n","Data sent…");
		}
	}
	
	else
	{
		while(1)
		{
			bzero(&buff1,sizeof(buff1));
			recv(sd,buff1,sizeof(buff1),0);
			printf("Received message from the server:%s\n",buff1);
		}
	}
	return 0;
}
