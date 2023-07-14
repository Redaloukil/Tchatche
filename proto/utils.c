#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include <string.h>

TchatcheMessage translate_buffer_to_message(char *buffer)
{
    TchatcheMessage message;
    
    char messageLength[4];
    char messageType[4];
    char* messageBody; 

    memset(messageLength, 0, 4);

    strncpy(message.messageLength, buffer, 4);
    strncpy(message.messageType, buffer+4, 4);

    size_t length = atoi(message.messageLength);

    message.messageBody = malloc((length) * sizeof(char));
    strncpy(message.messageBody, buffer+8, sizeof(char)*length);


    printf("Message Body: %s\n", message.messageBody);

    return message;
}
