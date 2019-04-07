#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<unistd.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main(int argc,char* argv[])
{ 
	int s=socket(AF_INET,SOCK_DGRAM,0);

	struct sockaddr_in sadd;
	sadd.sin_family = AF_INET;
  
	sadd.sin_port = htons(5669);

	socklen_t slen=sizeof(sadd);

	connect(s,(struct sockaddr*)&sadd,slen);

	while(1)
	{
		printf("Enter a message: ");
		char b[1024];
		fgets(b,sizeof(b),stdin);
		sendto(s,b,sizeof(b),0,(struct sockaddr*)&sadd,slen);
		printf("Message sent is %s\n",b);
                recvfrom(s,b,sizeof(b),0,(struct sockaddr*)&sadd,&slen);
                printf("Received data from server: %s",b);

	}   
	close(s);
}
