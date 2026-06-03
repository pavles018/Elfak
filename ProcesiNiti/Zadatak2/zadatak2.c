#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char* argv[]){
    if(argc>1){
        return -1;
    }
    else{
        execlp("tmp", argv[1], NULL);
    }
}