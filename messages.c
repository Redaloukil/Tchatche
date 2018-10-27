#define PSEUDO_LEN 10


struct Type {
    char type[4];
};   

struct Body {

};

struct Connexion {

};

struct Accept {

};

struct Fail {

};

struct Message {
    char message_len[4];
    struct Type type;
    struct Body body;
};
