#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#include<netdb.h>
#include<unistd.h>


int main(int argc, char *argv[])
{
int sock,portno,n;
char buffer[256];
struct sockaddr_in server;
struct hostent *server1;

if(argc<3)
	{
		perror("Please enter ip address and port no\n");
		exit(0);
	}
portno = atoi(argv[2]);

sock = socket(AF_INET,SOCK_STREAM,0);
if (sock<0)
	{
		perror("Socket Creation Failed\n");
	}
server1 = gethostbyname(argv[1]);

if(server1==NULL)
	{
		perror("NO such host avialable\n");
		exit(0);
	}

bzero((char *) &server, sizeof(server));


server.sin_family = AF_INET;
server.sin_port=htons(portno);
bcopy((char *) server1->h_addr, (char *) &server.sin_addr.s_addr,server1->h_length);

server.sin_port = htons(portno);

if(connect(sock,(struct sockaddr *) &server, sizeof(server))<0)
	{
		perror("Connection error\n");
		exit(0);
	}

printf("Enter the message to be sent to server : ");

bzero(buffer,256);
fgets(buffer,255,stdin);

n = write(sock,buffer,strlen(buffer));
if (n<0)
	{
		perror("Can't send the data to socket\n");
	}
bzero(buffer,256);

n = read(sock,buffer,256);
if (n<0)
	{
		perror("Data not received from the scoket\n");
	}
printf("%s\n",buffer);

close(sock);

return 0;

}

