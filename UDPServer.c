#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>


int main(int argc, char *argv[])
{
	int sock,length,fromlen,n,i,j,err=0;
	char buffer[256];
	struct sockaddr_in server,from;

	if (argc < 2)
	{	
		printf ("Plese provide pory no \n");
		exit(0);
	}
	sock = socket(AF_INET,SOCK_DGRAM , 0);

	if (sock < 0)
	{
		printf("Socket Creation Failed\n");
	}

	length = sizeof(server);
	bzero(&server,length);
	server.sin_family = AF_INET; 
        server.sin_addr.s_addr = INADDR_ANY; 
        server.sin_port= htons(atoi(argv[1])); 


	
	if(bind(sock, ( struct sockaddr *) &server, length) < 0)
	{
		printf( "Binding Failed" );
	}

	fromlen = sizeof (struct sockaddr_in);
	bzero(buffer,256);

	n = recvfrom ( sock ,buffer,256,0,(struct sockaddr *)&from ,&fromlen);
	if (n<0)
		{
			printf("data not received\n");
		}
	for(i=0;i<n;i++)
		printf("%c",buffer[i]);
	
	n = sendto(sock,"\nData is received on server\n",50,0,(struct sockaddr *)&from, fromlen);
	printf("The string sent by user is :");
	
	for(i=0;i<n;i++)
		printf("%c",buffer[i]);

	exit(0);
}

