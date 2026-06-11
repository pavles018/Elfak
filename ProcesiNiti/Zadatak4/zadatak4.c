#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 5
char reci[N][20]={"Ovo ", "je ", "test ", "za ", "niti!"};

struct argument{
    int nit;
    pthread_t prethodna_nit;
};

void * stampanje(void * arg){
    struct argument * zaStampu = (struct argument * ) arg;
    if(zaStampu->nit>0){
        pthread_join(zaStampu->prethodna_nit,NULL);
    }
    printf("%s\n", reci[zaStampu->nit]);
    sleep(3);
}

void main(int argc, char* argv[]){
    pthread_t Niti[N];
    struct argument argumenti[N];
    int i=0;
    for(i;i<N;i++){
        argumenti[i].nit=i;
        if(i>0)
          argumenti[i].prethodna_nit=Niti[i-1];
        pthread_create(&Niti[i], NULL,  (void *) stampanje, (void *) &argumenti[i]);
    }
    pthread_join(Niti[i-1],NULL);
}