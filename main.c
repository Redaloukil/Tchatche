#include<stdio.h>
#include<stdlib.h>

typedef struct message {
    char length[4];
    char type[4];
    char chaineLength[4];
} message;

typedef struct Client {
    int id;
    char *pseudo;
}Client;

void main(){
    int start = 1;
    Client client;
    client.id = 1;
    
    client.pseudo = "reda"; 
    
    printf("%d" , client.id);
    printf("%c" , ((char) client.pseudo));
    
}