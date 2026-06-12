/*Korišćenjem programskog jezika C napisati Linux progam koji sadrži bafer u koji se mogu smestiti dva
integer broja. Zasebna nit periodično generiše dva broja (u opsegu od 1 do 10) i upisuje ih u ovaj bafer.
Kada se u baferu nađe novi par brojeva glavna nit (main funkcija) treba da odredi zbir ta dva broja i
odštampa ga na standardnom izlazu. Vremenski razmak između dva uzastopna upisa u bafer je slučajna
vrednost između 0 i 5 sekundi.*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>

#define N 2

int buf[N];

pthread_mutex_t mutex;
pthread_cond_t condVarFull;
pthread_cond_t condVarEmpty;
int bufferFull=0;

void * funkcija(){
    while(1){
        pthread_mutex_lock(&mutex);
        while(bufferFull){
            pthread_cond_wait(&condVarEmpty,&mutex);
        }
        buf[0]=(int) rand()%10+1;
        buf[1]=(int) rand()%10+1;
        bufferFull=1;
        pthread_cond_signal(&condVarFull);
        pthread_mutex_unlock(&mutex);
        sleep(rand()%6);
    }
}

void main(int argc, char* argv[]){
    pthread_t thread;
    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&condVarFull,NULL),
    pthread_cond_init(&condVarEmpty,NULL);
    srand(time(NULL));
    pthread_create(&thread,NULL,funkcija,NULL);
    while(1){
        pthread_mutex_lock(&mutex);
        while(!bufferFull){
            pthread_cond_wait(&condVarFull,&mutex);
        }
        printf("Zbir brojeva iz bafera %d + %d = %d\n", buf[0],buf[1], buf[0]+buf[1]);
        bufferFull=0;
        pthread_cond_signal(&condVarEmpty);
        pthread_mutex_unlock(&mutex);
}
}