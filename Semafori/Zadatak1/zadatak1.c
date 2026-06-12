#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>

#define N 5
char reci[N][20]={"Ovo ", "je ", "test ", "za ", "niti!"};

sem_t sems[N-1];

void * stampanje(void * arg){
    int * zaStampu =  (int *) arg;
    if(*zaStampu>0){
        sem_wait(&sems[*zaStampu-1]);
    }
    printf("%s\n", reci[*zaStampu]);
    sleep(1);
    if(*zaStampu<N);
        sem_post(&sems[*zaStampu]);
}

void main(int argc, char * argv[]){
    
    int i;
    int argumenti[N];
    pthread_t Niti[N];
    for(i=0;i<N;i++){
        argumenti[i]=i;
        sem_init(&sems[i],0,0);
        pthread_create(&Niti[i],NULL, stampanje, (void *) &argumenti[i]);
    }
    sem_wait(&sems[N-1]);

    for(i=0;i<N;i++){
        sem_destroy(&sems[i]);
    }
    return;
}
