#include <stdio.h>

#define EVER ;;

long fibonacci(int n);
long qtd = 0;

struct lista_fibonacci{
    int n;
    long result;
    struct lista_fibonacci *pnext;
};

struct lista_tasks{
    struct lista_fibonacci *pfib;
    struct lista_tasks *pnext;
};

int main(void){
    struct lista_fibonacci *pfib;
    for(long limit =0;;limit++){
        
    }
    int i;
    long result;
    for(i=0;;i++){
        result = fibonacci(i);
        printf("fibonacci{%d} = ld\n (%ld calls)",i,result,qtd);
        qtd = 0;
    }
    return 0;
}

long fibonacci(int n){
    /*qtd++;
    if(n<= 1){
        return n;
    }

    return fibonacci(n-1) + fibonacci(n-2);*/

    //versão não recursiva
    long a = 0,b = 1,c;

    if(n == 0){
        return 0;
    }

    for(int i =2;i<=n;i++){
        qtd++;
        c = a + b;
        a = b;
        b = c;
    }

    return b;
}