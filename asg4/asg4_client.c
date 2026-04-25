#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 4570
#define CLIENT_IP "127.0.0.2"
#define CLIENT_PORT 4561
void main(){
        struct sockaddr_in client, server;
        int sd;
        char msg[512];
        bzero((char*)&server, sizeof(server));
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = inet_addr(SERVER_IP);
        server.sin_port = htons(SERVER_PORT);

	bzero((char*)&client, sizeof(client));
        client.sin_family = AF_INET;
        client.sin_addr.s_addr = inet_addr(CLIENT_IP);
        client.sin_port = htons(CLIENT_PORT);

        sd = socket(AF_INET, SOCK_STREAM, 0);
        connect(sd, (struct sockaddr*)&server, sizeof(server));

                do{
                        printf("Enter a Message: ");
             
fgets(msg, sizeof(msg), stdin);
msg[strcspn(msg, "\n")] = 0;
send(sd, msg, strlen(msg), 0);
               }while(strcmp(msg, "stop")!=0);
                
        close(sd);
}







