#include <netdb.h> 
#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h>
#include <arpa/inet.h>
#include "../proto/protocole.c"
#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 

int client_id;

int connection_response(char* message){
	char type[4];
	char response_body[10]; 
	
	bzero(type, sizeof(type));
	bzero(response_body , sizeof(response_body));

	printf("%s\n" , message);
	printf("%ld\n" , sizeof(message));
	
	type[0] = message[0];
	type[1] = message[1];
	type[2] = message[2];
	type[3] = message[3];

	printf("%c" , message[3]);
	//get response body --OKOK --BADD
	memcpy(response_body, message + 4, 2);
	
	printf("response type %s \n" , type);
	printf("response body %s \n" , response_body);
	
	if(memcmp(type , "OKOK", sizeof("OKOK")) == 0){
		return 0;
	}
	if(memcmp(type , "BADD", sizeof("BADD")) == 0){
		return 1;
	}
}	

void chat(int sockfd){
	for(;;){
		printf("start chatting");
	}
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
	            bzero(buff, sizeof(buff));
				memcpy(buff , HELO , sizeof("HELO"));
		        printf("SEND : %s\n" , buff);
		        
				write(sockfd, buff, sizeof(buff)); 
		        
				bzero(buff, sizeof(buff)); 
		        
				read(sockfd, buff, sizeof(buff));
				int response = connection_response(buff);
				if (response == 0){
					break;
				}
				//if response is positive , create new chat thread
				else {
					printf("connection accepted");
				}

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
    //extract type
    char type[4];
	memcpy(&type , message , 4);
    printf("%s" , type);
	char *message_body = "";
}