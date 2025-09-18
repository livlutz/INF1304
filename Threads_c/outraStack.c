#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void *thread(void *vargp);

char **p; //ponteiro global para as mensagens -> todas as threads tem acesso a esse ponteiro

int main (void) {
	long i;
	pthread_t tid; /** Identificador da thread */

    //Está na stack da função main
	char *vMsgs[] = {
		"Primeira mensagem",
		"Segunda mensagem"
	};

	p = vMsgs; //ponteiro agora aponta para o vetor de mensagens

    fprintf(stderr, "Vou criar as threads\n");
	for (i=0; i<2; i++){
        //(void *) i entra como os ponteiros dos argumentos -> valor de i
        int rc = pthread_create(&tid, NULL, thread, (void *) i);
        if(rc){
            fprintf(stderr, "ERRO: pthread_create() retornou %d\n", rc);
            exit(1);
        }
    }

	fprintf(stderr, "Fim da thread principal\n");
	pthread_exit(NULL);

	return 0;
}

/**
 * Função executada pela nova thread
 * @param vargp Argumento passado para a thread (índice da mensagem)
 * @return NULL
 */
void *thread(void *vargp) {
	int id;
	static int sVar = 0; //static é 1 por função e não por thread, as threads vão acessar a mesma variável sVar

	id = (long) vargp;
    //++sVar é pra incrementar antes de imprimir
	printf ("Thread %d: %s (sVar = %d)\n", id, p[id], ++sVar);
	sleep (30);

	return NULL;
}