#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#define BUFFSIZE 4096
/* 
This program get the inputs and read directly them into the file
./a.out > file : get the inputs and read it at 'file'. If that file does not exits, make it.

./a.out < infile > outflie : read the 'infile' and write it at 'outfile'. If 'outfile' does not exist, make it. This process is copying 'infile' to 'outfile'.
*/

int main(){
	int n;
	char buf[BUFFSIZE];
	while((n = read(STDIN_FILENO, buf, BUFFSIZE))>0)
		if(write(STDOUT_FILENO, buf, n)!=n)
			printf("write error\n");

	if(n<0)
		printf("read error\n");

	exit(0); // this function exits in stdlib.h
	return 0;
} 
