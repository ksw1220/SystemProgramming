#include<unistd.h>
#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#define PORT 8080
#define BUFFSIZE 1024
int main(int argc, char const *argv[]){
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[BUFFSIZE];
	char *hello = "Hello from server";
	int fd = open("send_f.txt",O_RDONLY);
	int len;
	// socket file descriptor를 생성한다.
	if((server_fd = socket(AF_INET, SOCK_STREAM, 0))==0){
		// error 처리
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	// socket option을 설정한다.
	if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt))){
		// error 처리
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);
	// bind를 실행한다.
	if(bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0){
		// error 처리
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	// listen를 실행한다.
	if(listen(server_fd, 3)<0){
		// error 처리
		perror("listen");
		exit(EXIT_FAILURE);
	}
	// accpet를 실행한다.
	if((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0){
		// error 처리
		perror("accept");
		exit(EXIT_FAILURE);
	}
	// accept가 성공한 경우 server와 client간의 전송  
	// file을 읽어 client에게 전송한다.
	while((len = read(fd, buffer, BUFFSIZE))!=0){
		write(new_socket, buffer, len);
	}
	// shutdown을 실행한다.

	if(shutdown(new_socket, SHUT_WR)==-1){
		// error 처리
		perror("shutdown() error");
		exit(EXIT_FAILURE);
	}
	// client로 부터의 message를 수신
	len = read(new_socket, buffer, BUFFSIZE);
	write(1,buffer,len);
	close(fd);
	close(new_socket);
	return 0;
}
