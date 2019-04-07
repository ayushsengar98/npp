#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdio.h>
#include<netdb.h>
#include<string.h>

int main(int argc,char *argv[])
{
	int n,sd,cd;
	struct sockaddr_in servaddr,cliaddr;
	socklen_t servlen,clilen;
	char buff[10000],buff1[10000];
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr(argv[1]);
	servaddr.sin_port=htons(5000);
	sd=socket(AF_INET,SOCK_STREAM,0);
cd=connect(sd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	if(!fork())
        { while(1)
           {fgets(buff,sizeof(buff),stdin);
            send(sd,buff,sizeof(buff),0);
            printf("client side sent: %s",buff);

            }
         }
        else
        {  while(1)
          {
            recv(sd,buff1,sizeof(buff1),0);
            printf("server side sent: %s",buff1);

            }

        }
	close(sd);
}


