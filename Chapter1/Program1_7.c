#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<string.h>

#define MAXLINE 4096
int main(){
	char buf[MAXLINE];
	pid_t pid;
	int status;

	printf("%% ");
// By using fgets, get the string which is name for process.
	while(fgets(buf, MAXLINE, stdin)!=NULL){ 
// Replace '\n' to NULL.
		if(buf[strlen(buf)-1] == '\n')      
			buf[strlen(buf)-1] = 0;
// By using fork(), create the child process.
		if((pid = fork())<0){                         // if fork() < 0, error. 
			printf("fork error\n");
		}	
		else if(pid == 0) {                           // if fork() == 0, child.
			execlp(buf, buf, (char *)0);
			printf("couldn't execute: %s\n", buf);
			exit(127);
		}
// By using waitpid() wait the termination of child process.
		if((pid = waitpid(pid, &status, 0))<0)        // if fork() > 0, parent.
			
			printf("waitpid error\n");
		printf("%% ");
	}
	exit(0);
}
			
