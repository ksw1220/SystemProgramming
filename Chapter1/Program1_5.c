#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

/* Promgram 1_5 uses the buffer and file. But this standard I/O gets the input and print it direclty, not stores it in the file.
*/

int main(){
	int c;
	
	while((c = getc(stdin)) !=EOF)
		if(putc(c,stdout) == EOF)
			printf("output error\n");

	if(ferror(stdin))
		printf("input error\n");
	
	exit(0);
}

