#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<signal.h>

#define SIZE sizeof(struct sockaddr_in)

void main(){
	int sockfd;
	char send_c,recv_c;
	struct sockaddr_in server={AF_INET,htons(1234)};

	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	if((sockfd = socket(AF_INET,SOCK_STREAM,0))==-1){
		printf("Socket Open Fail\n");
		exit(1);
	}
	
	if((connect(sockfd,(struct sockaddr *)&server,SIZE))==-1){
		printf("Connect fail\n");
		exit(1);
	}

	recv_c = '\n';
	while(1){
		if(recv_c == '\n')
			printf("type a letter\n");
		send_c = getchar();

		send(sockfd,&send_c,1,0);

		if(recv(sockfd,&recv_c,1,0)>0)
			printf("%c",recv_c);
		else {
			printf("No reply from server\n");
			close(sockfd);
			exit(1);
		}
	}
}
