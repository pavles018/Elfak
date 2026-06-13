/*Korišćenjem programskog jezika C kreirati višenitni Linux proces. U okviru procesa se izvršavaju tri
niti (N1, N2 i N3) koje pristupaju deljivom resursu. Deljivi rersurs je predstavljen celobrojnim nizom
od 20 elemenata. Niti pristupaju deljivom resursu na sledeći način:
• Nit N1, na svake 2 sekunde, upisuje slučajnu vrednost na slučajnu poziciju u prvoj polovini niza
(pozicije 0 do 9).
• Nit N2, na svake 4 sekunde, upisuje slučajnu vrednost na slučajnu poziciju u drugoj polovini
niza (pozicije 10 do 19).
• Nit N3, na svakih 8 sekundi, upisuje slučajnu vrednost na slučajnu poziciju u nizu (pozicije 0 do
19).
Korišćenjem nekog od poznatih mehanizama za sinhronizaciju i međusobno isključenje niti, obezbediti
da nit N3 može da pristupi deljivom resursu samo ako u datom trenutku deljivom resursu ne pristupa ni
nit N1 ni nit N2.*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define N 20

int arr[N];
pthread_mutex_t mutex1, mutex2;
pthread_t thread1, thread2, thread3;

void Nit1(){
    while(1){
        int vrednost=rand()%100;
        pthread_mutex_lock(&mutex1);
        int mesto=rand()%10;
        arr[mesto]=vrednost;
        pthread_mutex_unlock(&mutex1);
        sleep(2);
    }
}

void Nit2(){
    while(1){
        int vrednost=rand()%100;
        pthread_mutex_lock(&mutex2);
        int mesto=rand()%10+10;
        arr[mesto]=vrednost;
        pthread_mutex_unlock(&mutex2);
        sleep(4);
    }
}

void Nit3(){
    int vrednost=rand()%100;
    while(1){
        pthread_mutex_lock(&mutex1);
        pthread_mutex_lock(&mutex2);
        int mesto=rand()%20;
        arr[mesto]=vrednost;
        pthread_mutex_unlock(&mutex1);
        pthread_mutex_unlock(&mutex2);
        sleep(8);
    }
}


int main(int argc, char * argv[]){
    
    for(int i=0;i<20;i++){
        arr[i]=i+1;
    }

    srand(time(NULL));
    
    pthread_mutex_init(&mutex1,NULL);
    pthread_mutex_init(&mutex2,NULL);
    
    pthread_create(&thread1, NULL, (void *) Nit1, NULL);
    pthread_create(&thread2, NULL, (void *) Nit2, NULL);
    pthread_create(&thread3, NULL , (void *) Nit3, NULL);

    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    pthread_join(thread3,NULL);

    pthread_mutex_destroy(&mutex1);
    pthread_mutex_destroy(&mutex2);

}
