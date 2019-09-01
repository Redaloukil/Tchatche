typedef struct Length {
    
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


int main(){
    
    Protocole message;

    message.t = "HELO";
    message.l = "0013"; 
    message.b = "HELLLO WORLD THIS ME";

    
    
    return 0;
}



