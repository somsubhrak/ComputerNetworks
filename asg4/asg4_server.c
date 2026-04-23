#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 4570

void main(){
	struct sockaddr_in client, server;
	int sd, nsd, clen = sizeof(client);
	char msg[512];
	bzero((char*)&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_port = htons(SERVER_PORT);
	
	sd = socket(AF_INET, SOCK_STREAM, 0);
	bind(sd, (struct sockaddr *)&server, sizeof(server));
	listen(sd,5);
	printf("Before accept \n");
	while(1){
		nsd = accept(sd, (struct sockaddr*)&client, &clen);
		printf("After accept \n");
		do{
			memset(msg, 0x0, 512);
			recv(nsd, msg, 512, 0);
			printf("Message received: %s",msg);
			printf("Client IP: %s", inet_ntoa(client.sin_addr));
			printf("Client Port: %d", ntohs(client.sin_port));
		}while(strcmp(msg, "stop"));
		close(nsd);
	}
	close(sd);
}


