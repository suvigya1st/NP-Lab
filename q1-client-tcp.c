#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#define MAXSIZE 50

int main()
{
	int sockfd,retval;
	int recedbytes,sentbytes;
	struct sockaddr_in serveraddr;
	char buff[MAXSIZE], buff2[MAXSIZE], buff3[MAXSIZE];
	
	//int x;
	//printf("\nEnter port number :");
	//scanf("%d", x);

	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
		printf("\nSocket Creation Error");
	}
	printf("sockfd value :%i",sockfd);
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(3392);
	serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	retval=connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
	if(retval==-1)
	{
		printf("Connection error");
	}
	printf("\nEnter 5 numbers\n");
	//gets(buff)
	for (int i=0;i<5;i++)
	{
		scanf("%s",buff);
		sentbytes=send(sockfd,buff,sizeof(buff),0);
		if(sentbytes==-1)
		{
			printf("!!");
			close(sockfd);
		}
		//recedbytes=recv(sockfd,buff,sizeof(buff),0);
		//printf("current i = %d", i);
	}
	
	while(1)
	{
		printf("\nEnter choice:\n1: Search, 2:Sort, 3:Split odd-even, 4:Exit\n");
		int choice;		
		char choice_buff;
		scanf("%d", &choice);
		printf("%d", choice);
		choice_buff = choice + '0';
		//choice_buff[1] = '\0';
		printf("%c", choice_buff);
		printf("Before sending the choice");
		sentbytes=send(sockfd,&choice_buff,sizeof(choice_buff),0);
		if(sentbytes==-1)
		{
			printf("!!");
			close(sockfd);
		}
		printf("Switch Case start");
		switch(choice)
		{
			case 1:
				printf("\nEnter search number :");
				char search_no[2];
				scanf("%s", search_no);
				sentbytes = send(sockfd, search_no, sizeof(search_no), 0);
				if(sentbytes==-1)
				{
					printf("!!");
					close(sockfd);
					break;
				}
				char search_pos[2];
				recedbytes=recv(sockfd,search_pos,sizeof(search_pos),0);
				puts(search_pos);
				printf("\n");
				break;
			case 2:
				printf("\nEnter choice: \n1: Ascending, 2: Descending\n");
				char sort_choice[2];
				scanf("%s", sort_choice);
				sentbytes = send(sockfd, sort_choice, sizeof(sort_choice), 0);
				if(sentbytes ==-1)
				{
					printf("!!");
					close(sockfd);
					break;
				}
				//char buff2[MAXSIZE];
				recedbytes=recv(sockfd,buff2,sizeof(buff2),0);
				puts(buff2);
				printf("\n");
				break;
			case 3:
				//char buff3[MAXSIZE];
				recedbytes=recv(sockfd,buff3,sizeof(buff3),0);
				printf("\nOdd numbers :\t");
				puts(buff3);

				recedbytes=recv(sockfd,buff3,sizeof(buff3),0);
				printf("\nEven numbers :\t");
				puts(buff3);
				break;
			case 4:
				printf("EXITING !!!");
				break;
		}
	}	
	close(sockfd);
}
