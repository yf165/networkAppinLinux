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
	socklen_t cliAddrLen = sizeof(struct sockaddr_in);
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
	ret = bind(sockfd, (struct sockaddr *)&serAddr,sizeof(struct sockaddr_in));
	if(ret < 0){
		perror("bind");
		return -1;
	}	
	ret = listen(sockfd,MAXLENCON);
	if(ret < 0){
		perror("listen");
		return -1;
	}		
	accptSockfd = accept(sockfd,(struct sockaddr *)&cliAddr,&cliAddrLen);
	if(accptSockfd < 0){
		perror("accept");
		return -1;
	}		
	s_addr = cliAddr.sin_addr.s_addr;
	inet_ntop(AF_INET,&s_addr,bufIP,sizeof(bufIP));
	printf("accept connection from %s at %d\n",bufIP,cliAddr.sin_port);
	send(accptSockfd,&dataBuf,sizeof(dataBuf),0);
	close(sockfd);
	close(accptSockfd);
	return 0;
}