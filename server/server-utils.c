#include<pthread.h>

int server_protocol(char *buff){
    printf("server protocol interpretation :\n");
    //read the buffer and extract the message type
    char type[4];
    type[0] = buff[4];
    type[1] = buff[5];
    type[2] = buff[6];
    type[3] = buff[7];
}   




