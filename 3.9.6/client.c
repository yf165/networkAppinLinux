#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#define SERPORT 6003
#define SERIP "151.146.92.154"
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
	while(1){
		ret = recv(sockfd,&dataBuf,sizeof(dataBuf),0);
		printf("data from server :%s\n",dataBuf);
		printf("continue receive\n");
		scanf("%s",dataBuf);
		ret = send(sockfd,&dataBuf,sizeof(dataBuf),0);		
		if(ret < 0){
			perror("send");
			close(sockfd);
			return -1;
		}
		if(strncmp(dataBuf,"end",3) == 0){
			printf("client end\n");
			break;
		}
	} 
	close(sockfd);
	return 0;
}