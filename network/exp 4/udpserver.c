#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>


int main(int argc,char* argv[])
{ 
	int s=socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in sadd;
	sadd.sin_family=AF_INET;
	sadd.sin_addr.s_addr=htonl(INADDR_ANY);
	sadd.sin_port=htons(5669);

	socklen_t slen=sizeof(sadd);

	bind(s,(struct sockaddr*)&sadd,slen);
	printf("Server Connected!\n ");

	listen(s,4);

	struct sockaddr_in cadd;

	socklen_t clen=sizeof(cadd);

	int a=accept(s,(struct sockaddr*)&cadd,&clen);

	printf("Client Connected!");

	while(1)

	{ 
		char b[1024];
		recvfrom(s,b,sizeof(b),0,(struct sockaddr*)&cadd,&clen);
		printf("Message: %s",b);
                sendto(s,b,sizeof(b),0,(struct sockaddr*)&cadd,clen);
                printf("Send data to udp client:%s",b);
	}
	close(s);
	return 0;   
}
