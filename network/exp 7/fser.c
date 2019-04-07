#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<unistd.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
int main(int argc,char *argv[])
{
int ad,sd;
struct sockaddr_in servaddr,cliaddr;
socklen_t servlen,clilen;
char buff[1000],buff1[1000];
pid_t cpid;
bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
servaddr.sin_port=htons(5500);   
sd=socket(AF_INET,SOCK_STREAM,0);
bind(sd,(struct sockaddr*)&servaddr,sizeof(servaddr));
listen(sd,5);
printf("%s\n","Server is running.......");
ad=accept(sd,(struct sockaddr*)&cliaddr,&clilen);
 cpid=fork();
if(cpid==0) 
{
		while(1)
		{
			bzero(&buff,sizeof(buff));
			recv(ad,buff,sizeof(buff),0);
		printf("Received  message from the client:%s\n",buff);
	}
}
else
{
 	 while(1)
   	 {
		bzero(&buff1,sizeof(buff1));
		printf("%s\n","Enter the input data:");
		fgets(buff1,10000,stdin);
		send(ad,buff1,strlen(buff1)+1,0);
		printf("%s\n","Data sent…");
 	 }
}
return 0;
}




