#include<stdio.h>
#include <stdlib.h>

void run(int runner){
    runner = 2;
}


int main(){
    int runner = 1;
    run(runner);


    printf("%d" , runner);

    return 0;
}
