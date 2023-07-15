#ifndef PROTOCOLE_H
#define PROTOCOLE_H

typedef struct TchatcheMessage
{
    char messageLength[5];
    char messageType[5];
    char* messageBody;
} TchatcheMessage;

#endif // PROTOCOLE_H