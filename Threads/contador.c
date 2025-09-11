#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

#define NTHREADS 4
#define NITERACOES 100000000

void *contador(void *pArg);
void inicializaSemaforo(sem_t *pSemaforo, int pshared, unsigned valor);
void P(sem_t *pSemaforo);
void V(sem_t *pSemaforo);

unsigned contagem = 0;
sem_t semaforo;

int main (void) {
    pthread_t vTid[NTHREADS];
    int i;
    for (i=0; i<NTHREADS; i++)
        pthread_create(&vTid[i], NULL, contador, NULL);
    for (i=0; i<NTHREADS; i++)
        pthread_join(vTid[i], NULL);
    if(contagem != NITERACOES * NTHREADS)
        printf("***Erro de contagem (%u)\n", contagem);
    else{
        printf("Infelizmente a contagem deu certo (%u)\n", contagem);
    }

    return 0;

}
void *contador(void *pArg) {
    int i;

    for(i=0; i<NITERACOES; i++) {
        P(&semaforo);
        contagem++;
        V(&semaforo);
    }
 return NULL;
}

/**
 * cria o semáforo
 * @Param pSemaforo : ponteiro para o semáforo
 * @Param pshared : flag indicando se o semáforo é compartilhado entre threads
 * @Param valor : valor do semáforo
 */
void inicializaSemaforo(sem_t *pSemaforo, int pshared, unsigned valor) {
 if(sem_init(pSemaforo, pshared, valor) == -1) {
    fprintf(stderr, "Erro na inicialização do semáfor exit(1)");
 }
}

void P(sem_t *pSemaforo) {
    if(sem_wait(pSemaforo) == -1) {
        fprintf(stderr, "Erro em P");
        exit(2);
    }
}

void V(sem_t *pSemaforo) {
    if(sem_post(pSemaforo) == -1) {
        fprintf(stderr, "Erro em V");
        exit(3);
    }
}