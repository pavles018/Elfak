#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_ARG_LENGTH 50
#define MAX_ARGS 20

int main(int argc, char* argv []){
    char* argumenti [MAX_ARGS];
    //rezervisemo mesta za argumente, argv[0] pokazuje na ime fajla, dok poslednji element pokazuje NULL
    argumenti[0]=(char *)malloc(MAX_ARG_LENGTH * sizeof(char) );
    strcpy(argumenti[0],"./zadatak1");
    for(int i=1;i<argc;i++){
        argumenti[i]=(char *)malloc(MAX_ARG_LENGTH*sizeof(char));
        strcpy(argumenti[i],argv[i]);
    }
    argumenti[argc]=NULL;


    if(fork()==0){
        //ako udje ovde onda je proces roditelj
        if(execv("./zadatak1", argumenti)<0){ // ovde se izvrsava execv
            //ako dodje ovde, execv je vratio negativnu vrednost sto ukazuje na gresku
            perror("Doslo je do greske pri izvrsenju programa");
            exit(1);
        }
        return 0;
    }
    else
        wait(NULL); // proces roditelj ceka da se zavrsi proces dete
    for(int i=0;i<argc;i++)
        free(argumenti[i]);
    
    return 0;
}