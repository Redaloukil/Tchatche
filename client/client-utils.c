#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <netinet/in.h> 
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include"client-utils.h"

#define PORT 9000 //Server port
#define SA struct sockaddr //socket adresse used to communicated with client 
#define MAX 1024 //Buffer size 


typedef struct client {
    int id; // client id
    char buffer[MAX];
    int sockfd; //socket connexion response
    struct sockaddr_in serveraddr; //server address
    int connected;
} client;


// int client_main_menu(){
//     int client_choice = 1;
    
//     printf("READY TO CONNECT TO THE SERVER\n");
//     printf("1 - YES\n");
//     printf("2 - NO\n");
    
//     return client_choice;
// }

void client_connect(client client){
    printf("connect client");

    bzero(client.buffer , sizeof(client.buffer));
    write(client.sockfd, client.buffer, sizeof(client.buffer));
    bzero(client.buffer, sizeof(client.buffer));
    read(client.sockfd, client.buffer, sizeof(client.buffer));
    printf("From Server : %s", client.buffer);

    // if ((strncmp(client.buffer, "exit", 4)) == 0) {
    //     printf("Client Exit...\n");
    //     break;
    // }
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

client client_server_connect(int id){
    
    client cli;
    
    cli.id = id;

    bzero(&cli.serveraddr, sizeof(cli.serveraddr));

    cli.serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    cli.serveraddr.sin_family = AF_INET;
    cli.serveraddr.sin_port = htons(PORT); 

    cli.sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (cli.sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully created.. \n"); 

    printf("%d\n",cli.sockfd);
    if(connect(cli.sockfd, (SA*)&cli.serveraddr, sizeof(cli.serveraddr)) != 0) { 
        printf("connection with the server failed...\n"); 
        exit(0); 
    } else
        printf("connected to the server..\n"); 

    return cli;
}

void client_main_menu(client client){
    int choice;
    printf("#######READY TO CONNECT TO THE SERVER#######\n");
    printf("1 - YES\n");
    printf("2 - NO\n");
    scanf("%d\n" , &choice);
    
    printf("you choosed : %d\n", choice);
    if (choice == 1){
        printf("hell");
        client_connect(client);
    }
        
}

int client_connected_main_menu(client client){
    int choice;
    printf("#######YOU ARE CONNECTED WELCOME########\n");
    printf("1 - SEND PUBLIC MESSAGE");
    printf("2 - SEND PRIVATE MESSAGE");

    scanf("%d\n" , &choice);

    if (choice == 1){
        printf("we will try to connect you");
        client_connect(client);
    }
}
