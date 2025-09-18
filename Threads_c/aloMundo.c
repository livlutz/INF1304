#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *outraThread(void *vargp);

int main (void) {
	pthread_t tid; /** Identificador da thread */

	fprintf(stderr, "Vou criar a thread\n");
	int rc = pthread_create(&tid, NULL, outraThread, NULL);
	if(rc){
        fprintf(stderr, "ERRO: pthread_create() retornou %d\n", rc);
        return 1;
        //para abortar o código seria melhor usar exit ao invés de return
    }

    //Espera a thread terminar
    fprintf(stderr, "Thread criada, esperando pelo término\n");
	rc = pthread_join(tid, NULL);
    if(rc){
        fprintf(stderr, "ERRO: pthread_join() retornou %d\n", rc);
        return 1;
    }
	fprintf(stderr, "Fim da thread principal\n");
	return 0;
}

/**q
 * Função executada pela nova thread
 * Formato Java doc
 * @param vargp Argumento passado para a thread (não usado)
 * @return NULL
 */
void *outraThread(void *vargp) {
	puts("Nova thread nascendo...");
	sleep (30);
	puts("Alo mundo!");
	return NULL;
}
