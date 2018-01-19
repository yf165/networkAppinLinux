#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

   
#define SERPORT 6003
#define SERIP "151.146.92.154"
#define MAXLENCON	100
typedef struct argForSubthread {
	int accptSockfd;
	struct sockaddr_in cliAddr;
	
}argForSubthread;

void *(funcForSubThread)(void *arg)
{
	int sockfdSubthread = ((argForSubthread *)arg)->accptSockfd;
	struct sockaddr_in cliAddr =((argForSubthread *)arg)->cliAddr;
	ssize_t ret = 0; 
	in_addr_t s_addr = 0;
	char dataBuf[100] ={"hello i'm server\n"};
	char bufIP[50] ={0};
	s_addr = cliAddr.sin_addr.s_addr;
	inet_ntop(AF_INET,&s_addr,bufIP,sizeof(bufIP));
	printf("accept connection from %s at %d\n",bufIP,cliAddr.sin_port);
	while(1){
		ret = send(sockfdSubthread,&dataBuf,sizeof(dataBuf),0);		
		if(ret < 0){
			perror("send");
			close(sockfdSubthread);
			return NULL;
		}
		ret = recv(sockfdSubthread,&dataBuf,sizeof(dataBuf),0);	
		printf("data from client %s at port %d:%s\n",bufIP,cliAddr.sin_port,dataBuf);
		if(ret < 0){
			perror("recv");
			close(sockfdSubthread);
			return NULL;
		}
		if(strncmp(dataBuf,"end",3) == 0){
			printf("thread end\n");
			break;
		}
	}
	close(sockfdSubthread);
	free(arg);
	return NULL;
}
int main()
{
	int ret = -1;
	int sockfd;
	struct sockaddr_in serAddr ={0};
	in_addr_t s_addr = 0;
	socklen_t cliAddrLen = sizeof(struct sockaddr_in);
	pthread_t subThread;
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
	while(1){
		argForSubthread *pArgForSubthread =  malloc(sizeof(argForSubthread));
		pArgForSubthread->accptSockfd = accept(sockfd,(struct sockaddr *)&pArgForSubthread->cliAddr,&cliAddrLen);
		if(pArgForSubthread->accptSockfd < 0){
			perror("accept");
			close(sockfd);
			return -1;		
		}			
		pthread_create(&subThread,NULL,funcForSubThread,pArgForSubthread);
	}
	close(sockfd);
	return 0;
}