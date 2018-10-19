#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
int main(){
	printf("Hello world from process ID %ld\n",(long)getpid());
	exit(0);
}
