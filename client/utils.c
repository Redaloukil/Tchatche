#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../proto/utils.h"

char* get_user_input() {
    char buffer[1024];
    char* input = NULL;
    size_t input_size = 0;

    printf("Enter your input: ");

    // Read user input
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        // Remove trailing newline character
        buffer[strcspn(buffer, "\n")] = '\0';

        // Allocate memory for the input string
        input_size = strlen(buffer) + 1;
        input = (char*)malloc(input_size * sizeof(char));

        // Copy the input to the allocated memory
        strncpy(input, buffer, input_size);
    }

    return input;
}

char* concatenate_message(TchatcheMessage* message) {
    size_t totalLength = atoi(message->messageLength) + 1;  // Total length including null character
    char* result = malloc(totalLength * sizeof(char));

    // Concatenate the message length, message type, and message body
    strcpy(result,message->messageLength);
    strcat(result,message->messageType);
    strcat(result,message->messageBody);

    return result;
}