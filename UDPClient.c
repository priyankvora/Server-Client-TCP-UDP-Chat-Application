#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>

void error( char *msg)
{
	perror(msg);
	exit(1);
}
int main(int argc, char *argv[])
{
	int sock,length,n,i,j,err=0;
	char buffer[256],right[256]="The username is right";
	struct sockaddr_in server,from;
	struct hostent *hp;
	if (argc != 3) 
	{	
		printf(" Please enter ip address and port no\n ");
		exit(1);
	}
	sock = socket(AF_INET,SOCK_DGRAM , 0);
	if (sock < 0)
		{
			error("Error opening socket");
		}
	server.sin_family = AF_INET;
	hp =gethostbyname(argv[1]);
	if ( hp==0)
		{		
			error("Unknown Host");
		}
	bcopy((char *)hp->h_addr, (char *)&server.sin_addr,hp->h_length);
	server.sin_port = htons(atoi(argv[2]));
	length = sizeof(struct sockaddr_in);

	printf( "\nPlease enter the data to be sent to the server:");
	bzero(buffer,256);
	fgets(buffer,255,stdin);

	n = sendto(sock,buffer,strlen(buffer),0,(struct sockaddr_in *)&server,length);

	bzero(buffer,256);

	n = recvfrom ( sock ,buffer,256,0,(struct sockaddr_in *) &server , &length);

	for(i=0;i<n;i++)
		printf("%c",buffer[i]);
}
