#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
int main(int argc, char* argv[])
{
int s = socket(AF_INET, SOCK_STREAM, 0);
struct sockaddr_in sadd;
sadd.sin_family= AF_INET;
sadd.sin_addr.s_addr = inet_addr("127.0.0.1");
sadd.sin_port = htons(1887);
socklen_t slen = sizeof(sadd);
connect(s, (struct sockaddr*) &sadd, slen);
while(1){
char command[50];
char content[10000];
printf("Enter command to execute: ");
scanf("%s",command);
send(s,command,sizeof(command),0);
printf("Command Sent!\n");
recv(s,content,sizeof(content),0);
printf("%s",content);
}
close(s);
}


