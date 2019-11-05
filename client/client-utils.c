#include<stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>

typedef struct client{
    int id; // client id
    int sockfd; //socket connexion response
    struct sockaddr_in serveraddr; //server address
} client;


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

int client_connect(int id){
    client cli;
    cli.id = id;
    cli.serveraddr.sin_addr.s_addr = '127.0.0.1';
    cli.serveraddr.sin_family = AF_INET
}