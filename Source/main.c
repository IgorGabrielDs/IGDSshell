#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "arquivo.h"
#include "input.h"


char style[4] = "seq";

int main(int argc, char *argv[]){
    while(1){
        printf("igds %s> ", style);
        if(argc > 1){
            ler_arquivo(argc, argv);
        }
        char frase[100] = "cd se mata -ls kys";
        
        //funçao input
        return 0;
    }
    return 0;
}