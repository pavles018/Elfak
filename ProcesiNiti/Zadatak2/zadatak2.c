#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
    if(argc>1){
        return -1;
    }
    else{
        int pid=fork();
        if (pid==0){
            if(execlp("ls","ls",  argv[1], "./tmp", NULL)<0){
                perror("Doslo je do greske");
                exit(1);
            }
        }
        else{
            wait(NULL);
        }
        return 0;
    }
}