#include <stdio.h>
#include <stdlib.h>
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define MAX 1024 
#define PORT 9000 
#define CLIENTS_NUM 20
#define SA struct sockaddr 

// Function designed for chat between client and server. 
void func(int sockfd) 
{ 
    char buff[MAX]; 
    int n; 
    
    // infinite loop for chat 
    for (;;) { 
        //listening through port for request

        //read request from clients

        //interpret the request by reading headers
        
        //buffer initialized to zero 
        bzero(buff, MAX);
        
        // read the message from client and copy it in buffer 
        read(sockfd, buff, sizeof(buff)); 
        
        // print buffer which contains the client contents 
        printf("From client: %s\t To client : ", buff); 
        
        bzero(buff, MAX); 
        
        n = 0; 
        // copy server message in the buffer 
        while ((buff[n++] = getchar()) != '\n');
        
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
int main(){ 
    int client_id = 0;
    int client_num = 0;
    
    int sockfd, connfd, len; 
    
    struct sockaddr_in servaddr, cli; 
    
    int RUN = 1;
  
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
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    servaddr.sin_port = htons(PORT); 
  
    // Binding newly created socket to given IP and verification 
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
        printf("socket bind failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully binded..\n"); 
  
    // Now server is ready to listen and verification 
    if ((listen(sockfd, CLIENTS_NUM)) != 0) { 
        printf("Listen failed...\n"); 
        exit(0); 
    } 
    else
        printf("Server listening..\n"); 
    
    
  
    // Accept the data packet from client and verification 
    connfd = accept(sockfd, (SA*)&cli, &len); 
    if (connfd < 0) { 
        printf("server acccept failed...\n"); 
        exit(0); 
    }else {
        client_id++;
        printf("server acccept the client %d...\n" , client_id);
    }

    func(connfd); 
    // After chatting close the socket 
    close(sockfd); 
} 
