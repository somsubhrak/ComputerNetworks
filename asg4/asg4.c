#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 4560

int main(){
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

        printf("Server waiting...\n");

        while(1){
                nsd = accept(sd, (struct sockaddr*)&client, &clen);
                printf("Client connected\n");

                do{
                        memset(msg, 0x0, 512);

                        int n = recv(nsd, msg, 512, 0);
                        if(n <= 0) break;

                        printf("Message received: %s\n", msg);
                        printf("Client IP: %s\n", inet_ntoa(client.sin_addr));
                        printf("Client Port: %d\n", ntohs(client.sin_port));

                }while(strcmp(msg, "stop") != 0);

                close(nsd);
        }

        close(sd);
        return 0;
}
