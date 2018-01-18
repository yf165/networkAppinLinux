#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERPORT 6003
#define SERIP "192.168.11.129"
#define MAXLENCON	100
int main()
{
	int ret = -1;
	int sockfd,accptSockfd;
	struct sockaddr_in serAddr ={0};
	struct sockaddr_in cliAddr ={0};	
	socklen_t cliAddrLen = 0;
	in_addr_t s_addr = 0;
	char bufIP[50] ={0};
	char dataBuf[100] ={"hello i'm server\n"};
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd < 0){
		perror("socket");
		return -1;
	}
	serAddr.sin_family = AF_INET;
	serAddr.sin_port =  htons(SERPORT);
	ret = inet_pton(AF_INET,SERIP,&s_addr);
	if(ret < 0){
		perror("inet_pton");
		return -1;
	}	
	serAddr.sin_addr.s_addr = s_addr;
	ret = connect(sockfd,(struct sockaddr*)&serAddr,sizeof(serAddr));
	if(ret < 0){
		perror("bind");
		return -1;
	}	
	close(sockfd);
	return 0;
}