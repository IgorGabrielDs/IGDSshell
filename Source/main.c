#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ler_arquivo.h"
#include "input.h"

int main(int argc, char *argv[]){
    while(1){
        if(argc > 1){
            ler_arquivo(argc, argv);
        }
        char frase[100] = "cd se mata -ls kys";
        input(frase);
        //funçao input
        return 0;
    }
    return 0;
}