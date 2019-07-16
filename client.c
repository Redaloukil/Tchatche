#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <netinet/in.h> 
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "messages.c"

#define MAX 80 //Buffer size 
#define PORT 8080 //Server port 
#define SA struct sockaddr //socket adresse used to communicated with client 

//CONNECTION REQUEST
void connection_request(char *buff , int sockfd ,char *pseudo , char *tube){
    bzero(buff, sizeof(buff));
    
    Header header;
    header.type[0] = "H";
    header.type[1] = "E";
    header.type[2] = "L";
    header.type[4] = "O";

    Connection connection;
    int pseudo_len = strlen(pseudo);
    int tube_len = strlen(tube);

    int message_len = sizeof(&header);

    

}

//LOGOUT REQUEST
void logout_request(char *buff , int sockfd){
    Header header;
    header.type[0] = "B";
    header.type[1] = "Y";
    header.type[2] = "E";
    header.type[3] = "E";

    Logout logout;

    logout.header = header;

}
//SEND MESSAGE
void send_message(){
    Header header;
    header.type[0] = "";
    header.type[0] = "";
    header.type[0] = "";
    header.type[0] = "";    
}

void client_request(int choice){
    switch(choice){
        case 0 : 
            printf("connect to the server loading..");
            connection_request();

        case 1 : 
            printf("quit the program..");
            exit(0);
    }
}

void func(int sockfd)
{
    char buff[MAX];
    int n;
    for (;;) {
        bzero(buff, sizeof(buff));
        printf("Enter the string : ");
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

void menu(){
    char buff[MAX];
    int n;
    int run = 1;
    int choice;
    while(run == 1){
        printf("##################################");
        printf("Hello world,what you wish to do ?");
        printf("1 - Connect to the server");
        printf("2 - Exit the program");
        scanf("you choice %d" , &choice);
        client_request(choice);
    }
}

  
int main() 
{ 
    int sockfd, connfd; 
    struct sockaddr_in servaddr, cli; 
  
    // socket create and varification 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully created.. \n"); 
        
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

    func(sockfd);
    
  
    // close the socket 
    close(sockfd); 
} 
