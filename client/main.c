#include <netdb.h> 
#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h>
#include <arpa/inet.h>
#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 

void interpret(char* message){
	printf("From Server : %s", message);
	 int message_size = sizeof(message);
    //extract
    if(memcmp(message , "HELO" , 4) === 0){
		return (char*)("HELO");
	};
	return (char*)("DECO");


}

void connection(int sockfd) { 
	char buff[MAX]; 
	int reader; 
	int select = 0;
	printf("DO YOU WANT TO CONNECT\n");
    printf("0 - NO\n");
    printf("1 - YES\n");

    scanf("%d", &select);

    switch(select){
		case 0:
		    break;
		case 1:
	            memcpy(buff , "HELO" , sizeof("HELO"));
		        bzero(buff, sizeof(buff)); 
		        reader = 0; 
		        while ((buff[reader++] = getchar()) != '\n'); 
		        write(sockfd, buff, sizeof(buff)); 
		        bzero(buff, sizeof(buff)); 
		        read(sockfd, buff, sizeof(buff));
				//read the response ( if accepted , get the id and pseudo and ) 
		       
				interpret(buff); 
		        if ((strncmp(buff, "exit", 4)) == 0) { 
			    printf("Client Exit...\n"); 
			        break; 
		        } 
	        break;
		default:
			break;   	
		} 
}


int main() { 
	char* pseudo;
	int sockfd, connfd; 
	struct sockaddr_in servaddr, cli; 

	// socket create and varification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("socket creation failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully created..\n"); 
	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	servaddr.sin_port = htons(PORT); 

	// connect the client socket to server socket 
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
		printf("connection with the server failed...\n"); 
		exit(0); 
	} 
	else
		printf("connected to the server..\n"); 

	// function for chat 
	connection(sockfd); 

	// close the socket 
	close(sockfd); 
} 


void send_connect_message(char pseudo , int sockfd , char buff ){
	
}

void send_deconnect_message(char pseudo , int sockfd , char buff){
	//
}

void translate(char* message){
    //get message size 
    int message_size = sizeof(message);
    //extract
    char type[4];
	memcpy(&type , message , 4);
    printf("%s" , type);

	char *message_body = "";
}