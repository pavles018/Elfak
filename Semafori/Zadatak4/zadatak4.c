/*Korišćenjem programskog jezika C napisati Linux program koji simulira komunikaciju između niti
korišćenjem celobrojnih bafera. Nit N0 generiše celobrojne podatke i upisuje ih u bafere B1, B2 i B3.
Prilikom upisivanja podataka, nit N0, najpre proverava da li u baferu B3 ima slobodnih pozicija i u tom
slučaju novi podatak upisuje u bafer B3. Ako je bafer B3 pun, proverava da li postoje slobodne pozicije
u baferu B1. Ako postoje, proizvođač N0 generisani podataka upisuje u bafer B1. Ukoliko je i bafer B1
pun novi podatak se upisuje u bafer B2 ukoliko on poseduje slobodne pozicije. Ukoliko ni u jednom
baferu nema slobodnih pozicija, nit N0 čeka, dok se u nekom od bafera ne oslobodi pozicija za upis
novog elementa. Niti N1, N2, N3 čitaju podatke iz bafera B1, B2, B3 i prikazje ih na standardnom
izlazu. Za sinhronizaciju između niti iskoristiti POSIX semafore.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define N1 10
#define N2 15
#define N3 20

int buf1[N1];
int buf2[N2];
int buf3[N3];

int empty1=N1;
int empty2=N2;
int empty3=N3;

int tail1=0;
int head1=0;
int tail2=0;
int head2=0;
int tail3=0;
int head3=0;

sem_t mutex1, mutex2, mutex3, emptyMutex;

void * Nit0(void * args){
    while(1){
        sleep(rand()%3);
        sem_wait(&emptyMutex);
        sem_wait(&mutex3);
        if(empty3>0){
            buf3[head3%N3]=rand()%100;
            empty3--;
            head3++;
            sem_post(&mutex3);
            continue;
        }
        else{
        sem_post(&mutex3);
        }
        sem_wait(&mutex1);
        if(empty1>0){
            buf1[head1%N1]=rand()%100;
            empty1--;
            head1++;
            sem_post(&mutex1);
            continue;
        }
        else{
            sem_post(&mutex1);
        } 
        sem_wait(&mutex2);
        if(empty2>0){
            buf2[head2%N2]=rand()%100;
            empty2--;
            head2++;
        }
        sem_post(&mutex2);
    }
}

void *Nit1(void * args){
    while(1){
        sem_wait(&mutex1);
        if(empty1<N1){
            printf("ocitan podatak: %d\n", buf1[tail1%N1]);
            tail1++;
            empty1++;
            sem_post(&emptyMutex);
        }
        sem_post(&mutex1);
        sleep(rand()%5);
    }
}

void *Nit2(void * args){
    while(1){
        sem_wait(&mutex2);
        if(empty2<N2){
            printf("ocitan podatak: %d\n", buf2[tail2%N2]);
            tail2++;
            empty2++;
            sem_post(&emptyMutex);
        }
        sem_post(&mutex2);
        sleep(rand()%10);
    }
}

void *Nit3(void * args){
    while(1){
        sem_wait(&mutex3);
        if(empty3<N3){
            printf("ocitan podatak: %d\n", buf3[tail3%N3]);
            tail3++;
            empty3++;
            sem_post(&emptyMutex);
        }
        sem_post(&mutex3);
        sleep(rand()%15);
    }
}

void main(int argc, char * argv[]){
    srand(time(NULL));
    pthread_t Niti[4];

    sem_init(&mutex1,0,1);
    sem_init(&mutex2,0,1);
    sem_init(&mutex3,0,1);
    sem_init(&emptyMutex,0,N1+N2+N3);

    pthread_create(&Niti[1],NULL, (void * ) Nit1, NULL);
    pthread_create(&Niti[2],NULL, (void * ) Nit2, NULL);
    pthread_create(&Niti[3],NULL, (void * ) Nit3, NULL);
    pthread_create(&Niti[0],NULL, (void * ) Nit0, NULL);

    for(int i=0;i<4;i++){
        pthread_join(Niti[i], NULL);
    }

    sem_destroy(&mutex1);
    sem_destroy(&mutex2);
    sem_destroy(&mutex3);
    sem_destroy(&emptyMutex);

}
