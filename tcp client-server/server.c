#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<errno.h>
#include<unistd.h>
#include<netinet/in.h>
#include<string.h>
int main()
{
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
	FILE *fptr;
	int sock;
	int connected,bytes_received;
	char ch;
	char send_data[1024],received_data[1024];
	int sin_size,flag = 0;


	if((sock=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("socket");
		exit(1);
	}


	server_address.sin_family=AF_INET;
	server_address.sin_port=htons(90190);
	server_address.sin_addr.s_addr=inet_addr("127.0.0.1");

	if(bind(sock,(struct sockaddr *)&server_address, sizeof(struct sockaddr))==-1)
	{
		perror("unable to bind");
		exit(1);
	}

	if(listen(sock,5)==-1)
	{
		perror("lsten");
		exit(1);
	}

	printf("tcp server is waiting for client on port 90190\n");
	sin_size=sizeof(struct sockaddr_in);
	connected=accept(sock,(struct sockaddr *)&client_address,&sin_size);

	while(1)
	{
		
		bytes_received=recv(connected,received_data,1024,0);
		received_data[bytes_received]='\0';

		/*while((bytes_received=recv(connected,received_data,1024,0))>0)
		{
			received_data[bytes_received]='\0';
			printf("%s\n", received_data);
		}*/
		printf("reciecved data is %s\n\n\n",received_data);
		
		
		fptr=fopen(received_data,"r");
		if(fptr==NULL)
		{
			strcpy(send_data,"FILE");
			send(connected,send_data,strlen(send_data),0);
		}
		ch = fgetc(fptr);

		while(ch != EOF)
		{
			send_data[flag] = ch;
			flag++;
			ch = fgetc(fptr);
		}
			send(connected,send_data,strlen(send_data),0);
			close(connected);
			break;
	}
}
