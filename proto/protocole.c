char helo[4] = "HELO";
char ok[4] = "OKOK";
char bad[4] = "BADD";
char bye[4] = "BYEE";
char pubm[4] = "BCST";
char prim[4] = "PRVT";
char list[4] = "LIST";
char shut[4] = "SHUT";
char dbg[4] = "DEBG";




typedef struct Length {
    char length[4]; 
} Length ;

typedef struct Type {
    char type[4]
} Type ;

typedef struct Body {

} Body ;

typedef struct Protocole {
    char *l;
    char *t;
    Body b;
} Protocole;



