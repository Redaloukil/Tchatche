#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include "../proto/protocole.h"


#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

struct client_info {
    int socket;
    char identifier[10];
};

int num_clients = 0;
struct client_info clients[MAX_CLIENTS];

pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

void send_to_all_clients(char *message) {
    int i;
    pthread_mutex_lock(&clients_mutex);
    for (i = 0; i < num_clients; i++) {
        if (send(clients[i].socket, message, strlen(message), 0) != strlen(message)) {
            printf("Error: Failed to send message to client %s\n", clients[i].identifier);
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

void send_to_private_client(char* identifier, char* message) {
    pthread_mutex_lock(&clients_mutex);
    for(int i=0; i<num_clients;i++) {
        if(strcmp(clients[i].identifier, identifier) == 0) {
            if(send(clients[i].socket, message, strlen(message),0 ) != strlen(message)) {
                printf("Error: Failed to send private message to client %s with username %s\n", clients[i].identifier);
            }
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}



void handle_client(void *arg) {
    int client_socket = *((int *)arg);
    char buffer[BUFFER_SIZE]; // Buffer specific for receiving socket stream
    char message[BUFFER_SIZE]; // Buffer specific for sending message via socket stream
    char client_identifier[10]; // client id set only after application connection request 

    memset(message, 0,BUFFER_SIZE);

    strcpy(message, "You are connected to the server");

    if(send(client_socket, message, strlen(message), 0) != strlen(message)) {
        printf("Error while sending socket connection response to the client");
    }

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);

        if (recv(client_socket, buffer, BUFFER_SIZE, 0) <= 0) {
            printf("Client disconnected (identifier: %s)\n", client_identifier);
            // Check if client_identifier has been set 
            if(strlen(client_identifier) > 0) {
                // Remove client_identifier from the connected client list
                pthread_mutex_lock(&clients_mutex);
                for (int i = 0; i < num_clients; i++) {
                    if (strcmp(clients[i].identifier, client_identifier) == 0) {
                        // Shift clients array to remove the client
                        for (int j = i; j < num_clients - 1; j++) {
                            clients[j] = clients[j + 1];
                        }
                        num_clients--;
                        break;
                    }
                }
                pthread_mutex_unlock(&clients_mutex);
            }
            

            // Broadcast client disconnection to all connected clients
            sprintf(message, "Client disconnected (identifier: %s)\n", client_identifier);
            send_to_all_clients(message);

            close(client_socket);
            pthread_exit(NULL);
        }

        printf("Received message from client %s: %s\n", client_identifier, buffer);

        TchatcheMessage receivedMessage;

        strncpy(receivedMessage.messageLength,buffer,sizeof(char)*4);
        strncpy(receivedMessage.messageType, buffer + 4, sizeof(char)*4);
        
        // Extract the message body
        size_t bodyLength = atoi(receivedMessage.messageLength) - 8;  // Calculate the message body length
        receivedMessage.messageBody = malloc((bodyLength + 1) * sizeof(char));
        strncpy(receivedMessage.messageBody, buffer + 8, bodyLength);

      

        if(strncmp(receivedMessage.messageType, helo, 4)== 0) {
            // Set client identification and return it to the client

            // Generate identifier for client
            pthread_mutex_lock(&clients_mutex);
            sprintf(client_identifier, "%d", num_clients+1);

            // Store client information
            clients[num_clients].socket = client_socket;
            strcpy(clients[num_clients].identifier, client_identifier);
         
            num_clients++;

            pthread_mutex_unlock(&clients_mutex);

            printf("New client connected (identifier: %s)\n", client_identifier);
            
            size_t messageLength = sizeof(helo) + sizeof(client_identifier);
            snprintf(message, sizeof(messageLength), "%04lu", messageLength);
            strncpy(message + 4, ok, sizeof(char)*4);
            strncpy(message + 8, client_identifier, sizeof(client_identifier));

            
        }

        if (strncmp(receivedMessage.messageType, bye, 4) == 0 ) {
            pthread_mutex_lock(&clients_mutex);
                int i;
                for (i = 0; i < num_clients; i++) {
                    if (strcmp(clients[i].identifier, client_identifier) == 0) {
                        // Shift clients array to remove the client
                        for (int j = i; j < num_clients - 1; j++) {
                            clients[j] = clients[j + 1];
                        }
                        num_clients--;
                        break;
                    }
            }

            pthread_mutex_unlock(&clients_mutex);
            
            size_t messageLength = sizeof(bye);
            snprintf(message, sizeof(messageLength), "%04lu", messageLength);
            strncpy(message + 4, bye, sizeof(char)*4);
        }
        
        if (send(client_socket, message, strlen(message), 0) != strlen(message)) {
            printf("Error: Failed to send message to client %s\n", client_identifier);
        }
    }
}

int main(int argc, char *argv[]) {
    int server_socket, client_socket, port;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    pthread_t tid;

    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        return 1;
    }

    port = atoi(argv[1]);

    // Create server socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error: Failed to create socket\n");
        return 1;
    }

    // Bind server socket to port
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);


    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("Error: Failed to bind socket to port %d\n", port);
        return 1;
    }

    // Set socket listener to accept new client connection, max client connected = MAX_CLIENTS
    if (listen(server_socket, MAX_CLIENTS) < 0) {
        printf("Error: Failed to listen for incoming connections\n");
        return 1;
    }

    printf("Server started on port %d\n", port);

    while (1) {
        // Accept incoming connection
        if ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len)) < 0) {
            printf("Error: Failed to accept incoming connection\n");
            continue;
        }

        // Create a new thread to handle client communication
        if (pthread_create(&tid, NULL, (void *)handle_client, &client_socket) != 0) {
            printf("Error: Failed to create thread for client\n");
            continue;
        }

        pthread_detach(tid);
    }

    return 0;
}