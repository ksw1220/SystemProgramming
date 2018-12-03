#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<signal.h>

#define SIZE sizeof(struct sockaddr_in)

void closesock(int sig);

int sockfd_connect;

int main(){
	int sockfd_listen;
	char c;
	struct sockaddr_in server = {AF_INET,htons(1234),INADDR_ANY};
	struct sigaction act;

	act.sa_handler = closesock;
	sigfillset(&(act.sa_mask));
	sigaction(SIGPIPE,&act,NULL);

	if((sockfd_listen=socket(AF_INET,SOCK_STREAM,0))==-1){
		printf("Socket Open Fail\n");
		exit(1);
	}
	if(bind(sockfd_listen,(struct sockaddr *)&server,SIZE)==0){
		printf("Bind Fail\n");
		exit(1);
	}

	if(listen(sockfd_listen,5)==-1){
		printf("listen fail\n");
		exit(1);
	}
	while(1){

		if((sockfd_connect = accept(sockfd_listen,NULL,NULL))==-1){
			printf("Accept fail\n");
			continue;
		}
		printf("Request Accepted\n");

		while(recv(sockfd_connect,&c,1,0)>0){
			printf("%c received\n",c);
			send(sockfd_connect,&c,1,0);
		}

		printf("sockfd_connect closed\n");
		close(sockfd_connect);
	}
	return 0;
}

void closesock(int sig){
	close(sockfd_connect);
	printf("connection lost\n");
	exit(1);
}

