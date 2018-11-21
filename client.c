#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>
#include <netinet/in.h> 

void main(){
    //CREATE THE SOCKET 
    int network_socket;
    network_socket = socket(AF_INET , SOCK_STREAM , 0);
    
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = "127.0.0.1";
    server_address.sin_port = htons(2000);
    //CONNECT THE SOCKET TO A PORT ON A SPECIFIED HOST 
    int connection = connect(network_socket ,(struct sockaddr*) &server_address , sizeof(server_address));
    if(connection<0){
        printf(">>> connection error !!!");
    }
    char server_response[1024];
    recv(network_socket , &server_response , sizeof(server_response) , 0);

    printf(">>> Already received the message from the server");
    

    close(network_socket);
    //SEND LOOP FUNCTION AND LISTEN TO SERVER RESPONSE
}