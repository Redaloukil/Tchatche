#ifndef PROTOCOLE_H
#define PROTOCOLE_H

char helo[4];
char ok[4];
char bye[4];
char pubm[4];
char bad[4];
char prim[4];
char list[4];
char shut[4];
char dbg[4];


typedef struct TchatcheMessage
{
    char messageLength[5];
    char messageType[5];
    char* messageBody;
} TchatcheMessage;

#endif // PROTOCOLE_H