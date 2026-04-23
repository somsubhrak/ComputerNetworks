#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 5600
#define MAX 100
void countsort(int a[], int size){
	int max=a[0];
	for(int i=1;i<size;i++)
		if(a[i]>max)
			max=a[i];
	int count[max+1];
	memset(count, 0,sizeof(count));
	
	for(int i=0;i<size;i++)
		count[a[i]]++;
	
	int index=0;
	for(int i=0;i<=max;i++)
		while(count[i]--)
			a[index++]=i;
}
int main(){
	struct sockaddr_in server, client;
	int sd,a[MAX], size,clen=sizeof(client);
	server.sin_family= AF_INET;
	server.sin_port= htons(SERVER_PORT);
	server.sin_addr.s_addr=inet_addr(SERVER_IP);
	sd= socket(AF_INET,SOCK_DGRAM,0);
	bind(sd,(struct sockaddr*)&server, sizeof(server));
	recvfrom(sd,&size, sizeof(size),0, (struct sockaddr*)&client, &clen);
	recvfrom(sd, a, sizeof(int)*size, 0, (struct sockaddr*)&client, &clen);
	printf("Received array: ");
	for(int i=0;i<size;i++)
		printf("%d ",a[i]);

	countsort(a, size);
	sendto(sd,a,sizeof(int)*size,0, (struct sockaddr*)&client,clen);
	close(sd);
	return 0;
}
	
	

