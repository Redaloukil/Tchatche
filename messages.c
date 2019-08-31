#define PSEUDO_LEN 10

typedef struct Message{
   char length[4];
} Messages;


typedef struct Header {
    char message_len[4];
    char *type[4];
} Header;


typedef struct SSResponse {
    Header header;
    char id[2];
} SSResponse;

typedef struct BSResponse {
    Header header;
    
} BSSResponse;

typedef struct Logout {
    Header header;
    char id[2];
} Logout;

typedef struct UserChat {
    Header message;
    char id[2];
    char *body;
} UserChat;


int calculate_message_length(){
    return 0;
}
