#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>

int main(int argc,char *argv[])
{
	int sock,newsock,portno,n;
	char buffer[256];
	struct sockaddr_in server,client;
	socklen_t addr_size;

if(argc<2)
	{
		printf("Port no is not provided\n");
		exit(1);
	}


sock=socket(AF_INET,SOCK_STREAM,0);

if(sock<0)
	{
		perror("Socket Creation Failed\n");
		
	}
bzero((char *) &server,sizeof(server));
portno = atoi(argv[1]);

server.sin_family = AF_INET;
server.sin_port = htons(portno);
server.sin_addr.s_addr = INADDR_ANY;

if(bind(sock,(struct sockaddr *) &server,sizeof(server))<0)
	{
		perror("Error in Binding\n");
	}

listen(sock,5);
	

addr_size = sizeof(client);
newsock = accept(sock,(struct sockaddr *) &client,&addr_size);

if (newsock<0)
	{
		perror("Acception Failed\n");
	}
bzero(buffer,256);

n = read(newsock,buffer,255);
if (n<0)
	{
		perror("Error on reading\n");
	}
printf("Client : Hello server, here is data for you: %s\n",buffer);

n=write(newsock,"server : Hello, client. I got your data\n",100);
if(n<0)
	{
		perror("Can not write to socket\n");
	}
close(newsock);
close(sock);

return 0;

}






