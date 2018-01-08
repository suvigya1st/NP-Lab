#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#define MAXSIZE 90


void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
 
// A function to implement bubble sort
void bubbleSort(int arr[], int n)
{
   int i, j;
   for (i = 0; i < n-1; i++)      
 
       // Last i elements are already in place   
       for (j = 0; j < n-i-1; j++) 
           if (arr[j] > arr[j+1])
              swap(&arr[j], &arr[j+1]);
}


int main()
{
	int sockfd,newsockfd,retval;
	socklen_t actuallen;
	int recedbytes,sentbytes;
	struct sockaddr_in serveraddr,clientaddr;
	int arr[5];

	char buff[MAXSIZE];
	int a=0;
	//int x;
	//printf("\nEnter port number :");
	//scanf("%d", x);	

	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
		printf("\nSocket creation error");
	}

	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(3392);
	serveraddr.sin_addr.s_addr=htons(INADDR_ANY);
	retval=bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
	if(retval==1)
	{
		printf("Binding error");
		close(sockfd);
	}

	retval=listen(sockfd,1);
	if(retval==-1)
	{
		close(sockfd);
	}

	actuallen=sizeof(clientaddr);
	newsockfd=accept(sockfd,(struct sockaddr*)&clientaddr,&actuallen);


	if(newsockfd==-1)
	{
		close(sockfd);
	}
	for (int i=0;i<5;i++)
	{
		recedbytes=recv(newsockfd,buff,sizeof(buff),0);

		if(recedbytes==-1)
		{
			close(sockfd);
			close(newsockfd);
		}
		arr[i] = (int)buff[0] - (int)'0';
		puts(buff);
		printf("%d\t",arr[i]);
		printf("\n");
		//scanf("%s",buff);
		//sentbytes=send(newsockfd,buff,sizeof(buff),0);

		//if(sentbytes==-1)
		//{
		//	close(sockfd);
		//	close(newsockfd);
		//}
	}
	
	while(1)
	{
		char choice;
		recedbytes=recv(newsockfd,&choice,sizeof(choice),0);
		
		if(recedbytes==-1)
		{
			close(sockfd);
			close(newsockfd);
		}
		printf("\nChoice is : %c", choice);
		printf("\n");
		break;
	}
	close(sockfd);
	close(newsockfd);
}
