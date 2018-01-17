#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#define IP "192.168.1.102"

int main(void)
{
	in_addr_t addr = 0;
	addr = inet_addr(IP);
	printf("addr = 0x%x\n",addr);
	return 0;

}
