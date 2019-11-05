#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <netinet/in.h> 
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "client-utils.c"

#define MAX 1024 //Buffer size 
#define SA struct sockaddr //socket adresse used to communicated with client 




void func(int sockfd)
{
    //Messaging buffer
    char buff[MAX];
    
    //Reading iterator
    int n;
    
    //wait for the client to read the message
    for (;;) {
        //Initialize messaging buffer
        bzero(buff, sizeof(buff));
    
            // send the message
        n = 0;
        while ((buff[n++] = getchar()) != '\n');

        write(sockfd, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
        printf("From Server : %s", buff);
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
    }
}

int main() 
{ 
    int choice;
    
    int id= 0;
    
    // choice = client_main_menu();
    // // client logic identification
    // printf("you choosed %d" , choice);
     
    client client = client_server_connect(id);
    id++;
    printf("%d" , client.id);
    // printf("%s" , client.serveraddr.sin_addr);
    

    // //client socket response and connection response
    // int sockfd; 
    // struct sockaddr_in serveraddr; 
  
    // // socket create and varification 
    // sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    // if (sockfd == -1) {  
    //     printf("socket creation failed...\n"); 
    //     exit(0); 
    // } 
    // else
    //     printf("Socket successfully created.. \n"); 
        
    // bzero(&serveraddr, sizeof(serveraddr)); 
  
    // // assign IP, PORT 
    // serveraddr.sin_family = AF_INET; 
    // serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    // serveraddr.sin_port = htons(PORT); 
  
    // // connect the client socket to server socket 
    // if (connect(sockfd, (SA*)&serveraddr, sizeof(serveraddr)) != 0) { 
    //     printf("connection with the server failed...\n"); 
    //     exit(0); 
    // } 
    // else
    //     printf("connected to the server..\n"); 
    
    // function for chat 
    client_main_menu(client);
    
    // // close the socket 
    // close(sockfd); 

    //start application menu 
} 
