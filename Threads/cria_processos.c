#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

int main(void){
    struct timespec inicio;
    struct timespec fim;

    clock_gettime(CLOCK_MONOTONIC, &inicio);

    for(int i = 0;i < 1000;i++){
        pid_t pid = fork();
        if(pid < 0){
            perror("fork");
            exit(1);
        }

        else if(pid == 0){
            exit(0);
        }

        else{
            //wait(10);
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &fim);
    double tempo = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
    printf("Tempo total: %f\n",tempo);
}


