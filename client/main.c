#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <netinet/in.h> 
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>


#define MAX 1024 //Buffer size 
#define PORT 8000 //Server port 
#define SA struct sockaddr //socket adresse used to communicated with client 


void client_main_menu(){
    int client_choice = 1;
    
    printf("READY TO CONNECT TO THE SERVER\n");
    printf("1 - YES\n");
    printf("2 - NO\n");

    switch (client_choice){
    case 1:
        printf("start connecting with the server\n");
        break;
    case 2:
        printf("Thank you for dear client..next time\n");
        break;
    default:
        break;
    }
}

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
    
    client_main_menu();
       

    //client logic identification
    
    
    //client socket response and connection response
    int sockfd; 
    struct sockaddr_in serveraddr; 
  
    // socket create and varification 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully created.. \n"); 
        
    bzero(&serveraddr, sizeof(serveraddr)); 
  
    // assign IP, PORT 
    serveraddr.sin_family = AF_INET; 
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    serveraddr.sin_port = htons(PORT); 
  
    // connect the client socket to server socket 
    if (connect(sockfd, (SA*)&serveraddr, sizeof(serveraddr)) != 0) { 
        printf("connection with the server failed...\n"); 
        exit(0); 
    } 
    else
        printf("connected to the server..\n"); 
  
    // function for chat 
    func(sockfd);
    
    // close the socket 
    close(sockfd); 
} 
