#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#define IP "192.168.1.102"

int main(void)
{
#if 0
	in_addr_t addr = 0;
	addr = inet_addr(IP);
	printf("addr = 0x%x\n",addr);

	int ret =0;
	struct in_addr addr;
	ret  = inet_pton(AF_INET, IP, &addr);
	if(ret != 1){
		printf("inet_pton eeor\n");
		return -1;
	}
	printf("addr = 0x%x\n",addr.s_addr);
#endif	
	const char *inet_ntop(int af, const void *src,
                             char *dst, socklen_t size);

	return 0;

}
