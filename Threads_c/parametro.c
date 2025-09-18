#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
	int   value;
	char  string[128];
} thread_parm_t;

void *threadfunc(void *parm);

int main(int argc, char *argv[]) {
	pthread_t             thread; //identificador da thread
	int                   rc;    //código de retorno das funções
	pthread_attr_t        pta;  //atributos da thread
	thread_parm_t         *parm=NULL; //parâmetros para a thread

    //cria o objeto de atributos da thread
	printf("Create a thread attributes object\n");
	rc = pthread_attr_init(&pta);
	if(rc) {
		fprintf(stderr, "pthread_attr_init() failed, rc=%d\n", rc);
		exit(1);
	}

    //cria threads com atributos e parâmetros
	printf("Create thread using the default attributes e vários parâmetros\n");
	/* Set up multiple parameters to pass to the thread */
	parm = malloc(sizeof(thread_parm_t));
    if(parm == NULL){
        fprintf(stderr, "malloc() failed\n");
        exit(1);
    }
	parm->value = 77;
	strcpy(parm->string, "Inside secondary thread");
	rc = pthread_create(&thread, &pta, threadfunc, (void *)parm);
	if(rc) {
		fprintf(stderr, "pthread_create() failed, rc=%d\n", rc);
		exit(1);
	}

    //destruir a lista de atributos
	printf("Destroy thread attributes object\n");
    //liberar recursos para evitar memory leak
	rc = pthread_attr_destroy(&pta);
	if(rc) {
		fprintf(stderr, "pthread_attr_destroy() failed, rc=%d\n", rc);
		exit(1);
	}
	rc = pthread_join(thread, NULL);
	if(rc) {
		fprintf(stderr, "pthread_join() failed, rc=%d\n", rc);
		exit(1);
	}

	printf("Main completed\n");
	return 0;
}

/**
 * Função executada pela nova thread
 * @param parm Parâmetro passado para a thread
 * @return NULL
 */
void *threadfunc(void *parm) {
	thread_parm_t *p = (thread_parm_t *)parm;
	printf("%s, parm = %d\n", p->string, p->value);
	free(p);
	return NULL;
}