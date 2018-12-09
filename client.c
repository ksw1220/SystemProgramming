// 컴네_2017029325_권순우
#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<arpa/inet.h>
#define PORT 8080
#define BUFFSIZE 1024
int main(int argc, char const *argv[]){
	struct sockaddr_in address;
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	char *hello = "Hello from client";
	char buffer[BUFFSIZE];
	int fd = open("recv_f.txt", O_WRONLY | O_CREAT | O_TRUNC);
	int len;
	// socket을 생성
	if((sock = socket(AF_INET, SOCK_STREAM,0))<0){
		// 실패할 경우 error message를 출력 후 종료
		printf("\n Socket creation error\n");
		return -1;
	}

	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	// IP주소를 text형식의 것에서 이진 형식의 것으로 변화
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0){
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}
	// connect 실행
	if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0){
		// error 처리
		printf("\nConnection Failed \n");
		return -1;
	}
	// server로 부터 받은 파일을 buffer에 저장
	while((len = read(sock,buffer,BUFFSIZE))!=0){
		// 저장된 buffer을 recv_f.txt에 저장
		write(fd,buffer,len);
	}
	// server에게 Thank you message를 전달
	write(sock,"Thaknk you\n",10);
	close(fd);
	close(sock);
	return 0;
}
