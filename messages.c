#define PSEUDO_LEN 10

typedef struct Message {
    char message_len[4];
    char type[4];
} Message;

typedef struct Connection {
    Message message;
    char *pseudo;
    char *tube;
} Connection;

typedef struct SResponse {
    Message message;
    char id[2];
} SResponse;   

typedef struct SResponse {
    Message message;
    char id[2];
} SResponse;   

typedef struct Logout {
    Message message;
    char id[2];
} Logout;

typedef struct UserChat {
    Message message;
    char id[2];
    char *body;
} UserChat;



