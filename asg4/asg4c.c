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
        struct sockaddr_in server;
        int sd;
        char msg[512];

        bzero((char*)&server, sizeof(server));
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = inet_addr(SERVER_IP);
        server.sin_port = htons(SERVER_PORT);

        sd = socket(AF_INET, SOCK_STREAM, 0);
        connect(sd, (struct sockaddr*)&server, sizeof(server));

        do{
                printf("Enter a Message: ");
                scanf("%s", msg);

                send(sd, msg, strlen(msg), 0);

        }while(strcmp(msg, "stop") != 0);

        close(sd);
        return 0;
}
