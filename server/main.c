#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <unistd.h>
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include "../proto/protocole.c"
#define MAX 80 
#define MAX_CLIENTS 50
#define PORT 8080 
#define SA struct sockaddr 

int clients[MAX_CLIENTS];

char* translate(char* message){
    //get message size 
	printf("message received from client %s" , message);
    int message_size = sizeof(message);
    //extract
    if(memcmp(message , "HELO" , 4) === 0){
		return (char*)("HELO");
	};
	return (char*)("DECO");

}

// Function designed for chat between client and server. 
void connection(int sockfd) { 
	char buff[MAX]; 
	int n;
    for (;;) { 
                bzero(buff, MAX); 

                // read the message from client and copy it in buffer 
                read(sockfd, buff, sizeof(buff)); 
                
                // translate message  
                char* response = translate(buff);

                bzero(buff, MAX); 
                n = 0; 
                // copy server message in the buffer 
                // while ((buff[n++] = getchar()) != '\n') ; 
                memcpy(buff , response , 4 );

                // and send that buffer to client 
                write(sockfd, buff, sizeof(buff)); 

                // if msg contains "Exit" then server exit and chat ended. 
                if (strncmp("exit", buff, 4) == 0) { 
                    printf("Server Exit...\n"); 
                    break; 
                } 
    }
    
} 

// Driver function 
int main() 
{ 
	int sockfd, connfd, len; 
	struct sockaddr_in servaddr, cli; 
	// socket create and verification 
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
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(PORT); 

	// Binding newly created socket to given IP and verification 
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
		printf("socket bind failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully binded..\n"); 

	// Now server is ready to listen and verification 
	if ((listen(sockfd, MAX_CLIENTS) != 0)) { 
		printf("Listen failed...\n"); 
		exit(0); 
	} 
	else
		printf("Server listening..\n"); 
	len = sizeof(cli); 

	// Accept the data packet from client and verification 
	connfd = accept(sockfd, (SA*)&cli, &len); 
	if (connfd < 0) { 
		printf("server acccept failed...\n"); 
		exit(0); 
	} 
	else
		printf("server acccept the client...\n"); 

	// Function for chatting between client and server 
	connection(connfd); 

	// After chatting close the socket 
	close(sockfd); 
} 
