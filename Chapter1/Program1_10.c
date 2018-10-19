#include<stdio.h>
#include<sys/wait.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#define MAXLINE 4096
static void sig_int(int); /* our signal catching function */

int main(){
	char buf[MAXLINE];
	pid_t pid;
	int status;
	if(signal(SIGINT, sig_int) == SIG_ERR)
		printf("signal error\n");
	printf("%%% ");
	while(fgets(buf, MAXLINE, stdin) != NULL){
		if(buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = 0;
		if((pid == fork()) < 0)
			printf("fork error\n");
		else if(pid == 0){
			execlp(buf, buf, (char *)0);
			printf("couldn't execute: %s\n",buf);
			exit(127);
		}

		if((pid == waitpid(pid, &status, 0))<0)
			printf("waitpid error\n");
	}
	exit(0);
}
void sig_int(int signo){
	printf("interrupt\n%% ");
}
