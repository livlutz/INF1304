#include <stdio.h>
#include <pthread.h>

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

struct task{
    struct numers *pthread;
    struct task* ptask;
};

int main(void){
    int n = 0;
    struct task *pfila = NULL;

    pthread_t thread;
    struct thread_parm_t param;
    phtread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    phtread_mutex_t file_mutex = PTHREAD_MUTEX_INITIALIZER;;
    phtread_cond_t cond = PTHREAD_COND_INITIALIZER;

    param.mutex

    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&file_mutex);
    pthread_cond_destroy(&cond);

    return 0;

}

/**
 * Cálculo da série de Fibonacci
 * Versão iterativa para evitar estouro de pilha
 *
 * @param n Número de série a ser calculada
 * @return retorna o número de fibonacci correspondente ao param n
 */

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