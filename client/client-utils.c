#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <netinet/in.h> 
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include"client-utils.h"

#define PORT 8000 //Server port
#define SA struct sockaddr //socket adresse used to communicated with client 


typedef struct client{
    int id; // client id
    int sockfd; //socket connexion response
    struct sockaddr_in serveraddr; //server address
} client;


int client_main_menu(){
    int client_choice = 1;
    
    printf("READY TO CONNECT TO THE SERVER\n");
    printf("1 - YES\n");
    printf("2 - NO\n");
    
    return client_choice;
}

client client_server_connect(int id){
    client cli;
    
    struct sockaddr_in serveraddr;
    cli.id = id;

    bzero(&serveraddr, sizeof(serveraddr));

    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(PORT); 

    cli.sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (cli.sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully created.. \n"); 

    
    
    if(connect(cli.sockfd, (SA*)&cli.serveraddr, sizeof(cli.serveraddr)) != 0) { 
        printf("connection with the server failed...\n"); 
        exit(0); 
    } else
        printf("connected to the server..\n"); 

    return cli;
}

int client_main_menu(){
    int client_choice = 1;
    
    printf("READY TO CONNECT TO THE SERVER\n");
    printf("1 - YES\n");
    printf("2 - NO\n");
    
    return client_choice;
}


void client_connect(){
    printf("connect client");
}

void client_logout(){
    printf("logout client");
}

void client_public_message(){
    printf("send public message");
}

void client_private_message(){
    printf("send private message");
}