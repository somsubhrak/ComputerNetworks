#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 5600
#define CLIENT_IP "127.0.0.1"
#define CLIENT_PORT 56001
#define MAX 100

int main()
{
	struct sockaddr_in server, client;
	int sd,size,a[MAX], slen=sizeof(server);
	server.sin_family= AF_INET;
        server.sin_port= htons(SERVER_PORT);
        server.sin_addr.s_addr=inet_addr(SERVER_IP);
        
        client.sin_family= AF_INET;
        client.sin_port= htons(CLIENT_PORT);
        client.sin_addr.s_addr=inet_addr(CLIENT_IP);
        sd= socket(AF_INET,SOCK_DGRAM,0);
        bind(sd,(struct sockaddr*)&client, sizeof(client));
	printf("Enter the size of array: ");
	scanf("%d",&size);
	printf("Enter the array: ");
	for(int i=0;i<size;i++)
                scanf("%d",&a[i]);

	sendto(sd, &size,sizeof(int),0, (struct sockaddr*)&server, slen);
	sendto(sd, a,sizeof(int)*size,0, (struct sockaddr*)&server, slen);
	recvfrom(sd, a, sizeof(int)*size,0, (struct sockaddr*)&server, &slen);
	printf("\nSorted array: ");
        for(int i=0;i<size;i++)
                printf("%d ",a[i]);
	close(sd);
	return 0;
}



