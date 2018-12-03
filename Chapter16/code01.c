#include<stdio.h>
#include<arpa/inet.h>
#include<unistd.h>

int main(){
	char *valid = "197.0.0.1";
	char *invalid = "300.0.0.1";

	in_addr_t ipaddr1;
	struct in_addr ipaddr2;

	if((ipaddr1=inet_addr(valid))==-1)
		printf("invalid: %s\n",valid);
	else 
		printf("valid: %d.%d.%d.%d\n",
				(ipaddr1>>0)&0xFF,(ipaddr1>>8)&0xFF,(ipaddr1>>16)&0xFF,(ipaddr1>>24)&0xFF);
