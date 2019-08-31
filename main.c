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

Client client_list[50];

void main(){
    int run = 1,choice;

    Client client;
    

    while(run){
        printf("################TCHATCH#######################\n");
        printf("HELLO TO TCHATCH APPLICATION\n");
        printf("CHOOSE AND OPTION : \n");
        printf("1 - CHOICE 1\n");
            
        printf("2 - CHOICE 2\n");
        printf("3 - CHOICE 3\n");
        printf("4 - QUIT 4\n");

        scanf("%d" , &choice);
        switch(choice){
            case 0:
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;         
        }
    }
    
    
}