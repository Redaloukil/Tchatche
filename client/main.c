#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "../proto/protocole.h"
#include "../proto/utils.h"
#include "utils.h"

#define BUFFER_SIZE 1024

TchatcheMessage get_connection_request_message() {
    TchatcheMessage message;

    printf("Choose a username : \n");
    char* username = get_user_input();

    printf("Choose a channel name to connect to : \n");
    char* tunnel = get_user_input();
    char* result = (char*)malloc((strlen(username) + strlen(tunnel) + 1) * sizeof(char));

    strcpy(result, username);
    strcat(result, tunnel);


    size_t bodyLength = strlen(result);

    size_t totalLength = 4 + 4 + bodyLength;
    
    snprintf(message.messageLength, sizeof(message.messageLength), "%04lu", totalLength);

    strncpy(message.messageType, "HELO", sizeof(char) * 4);
    
    int messageLength = atoi(message.messageLength);

    message.messageBody = malloc((bodyLength + 1) * sizeof(char));

    strncpy(message.messageBody, result, bodyLength);

    return message;
};

int main(int argc, char *argv[]) {
    int client_socket, port;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    char client_id[10];

    if (argc != 3) {
        printf("Usage: %s <server IP> <port>\n", argv[0]);
        return 1;
    }

    port = atoi(argv[2]);

    // Create client socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error: Failed to create socket\n");
        return 1;
    }

    // Set server address and port
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, argv[1], &(server_addr.sin_addr)) <= 0) {
        printf("Error: Invalid server IP address\n");
        return 1;
    }

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("Error: Failed to connect to the server\n");
        return 1;
    }

    // Receive identifier from the server
    memset(buffer, 0, BUFFER_SIZE);

    if (recv(client_socket, buffer, BUFFER_SIZE, 0) <= 0) {
        printf("Error: Failed to receive identifier from the server\n");
        close(client_socket);
        return 1;
    }

    printf("Connected to the server. %s", buffer);

    while (1) {
        printf("Enter 'q' to quit : \n");
        printf("Enter 'a' to connect to the chat application : \n");
        
        fgets(buffer, BUFFER_SIZE, stdin);

        // Remove trailing newline character
        buffer[strcspn(buffer, "\n")] = '\0';

        if(strcmp(buffer, "a") == 0 ) {
            TchatcheMessage tchatch_connection_message = get_connection_request_message();
            
            char* message = concatenate_message(&tchatch_connection_message);
           
            memset(buffer, 0, BUFFER_SIZE);

            strncpy(buffer, message,  strlen(message));

            if(send(client_socket, buffer, strlen(message), 0) != strlen(buffer)) {
                printf("Error: Failed to send connection message to the server\n");
            }

            memset(buffer, 0, BUFFER_SIZE);
            
            if(recv(client_socket, buffer, BUFFER_SIZE, 0) <= 0) {
                printf("Error: Failed to receive connection response from the server\n");
            }

            printf("Server response: %s\n", buffer);
            TchatcheMessage responseMessage = translate_buffer_to_message(buffer);

            if(strncmp(responseMessage.messageType, ok,4) == 0) {
                strncpy(client_id, responseMessage.messageBody, sizeof(char)*10);  
                printf("Your identifier is %s\n", client_id);

                free(responseMessage.messageBody);

                while(1) {
                    memset(buffer, 0,BUFFER_SIZE);
                    printf("You are connected through the communication channel \n");
                    printf("\n");
                    printf("Enter 'q' to disconnect from the channel\n");


                    fgets(buffer, BUFFER_SIZE, stdin);
                
                    size_t inputLength = strlen(buffer);

                    if (inputLength > 0 && buffer[inputLength - 1] == '\n') {
                        buffer[inputLength - 1] = '\0';
                    }

                    if(strcmp(buffer, "q") == 0) {

                        size_t length = 4 + 4+sizeof(client_id);

                        snprintf(buffer, sizeof(length), "%04lu", length);
                        strncpy(buffer + 4, bye, sizeof(char)*4);
                        strncpy(buffer+8, client_id,sizeof(char)*10);


                        if(send(client_socket, buffer, length, 0) != length) {
                            printf("Error: Failed to send disconnection message to the server\n");
                        }
                    }

                    memset(buffer, 0, BUFFER_SIZE);

                    if(recv(client_socket, buffer,BUFFER_SIZE, 0)<= 0) {
                        printf("Error: Failed to receive server response\n");
                    }

                    char *messageType;

                    strncpy(messageType, buffer + 4, sizeof(char)*4);

                    if(strcmp(messageType, pubm) == 0 ) {
                        printf("Server send the message publicly");
                    }

                    if(strcmp(messageType, bye)) {
                        break;
                    }
                }
            }
        }

        // Quit if 'q' is entered
        if (strcmp(buffer, "q") == 0) {
            break;
        }
    }

    // Close the client socket
    close(client_socket);
    return 0;
}


