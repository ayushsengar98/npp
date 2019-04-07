#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<unistd.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<time.h>

int main(int argc,char* argv[])
{ int s=socket(AF_INET,SOCK_STREAM,0);
  
  struct hostent *h;
  h=gethostbyname(argv[1]);

  struct sockaddr_in sadd;
  sadd.sin_family=AF_INET;
  memcpy((char*)&sadd.sin_addr.s_addr,h->h_addr_list[0],h->h_length);
  sadd.sin_port=htons(1999);

  socklen_t slen=sizeof(sadd);
  
  connect(s,(struct sockaddr*)&sadd,slen);

  char b[1024];
  recv(s,b,sizeof(b),0);
  printf("Time: %s\n",b);   
  close(s);
}
