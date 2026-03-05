#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "lista.h"
#include "main.h"

void input(Node *palavras){
        while (palavras != NULL){
            if(strcmp(palavras->texto, "style") == 0){
                if(palavras->proximo == NULL){
                    printf("\x1b[1m\nCodigo incompleto, coloque sequential ou parallel\x1b[0m\n\n");
                    break;
                }
                palavras = palavras->proximo;

                if(strcmp(palavras->texto, "parallel") == 0){
                    strcpy(style, "par");
                }else if(strcmp(palavras->texto, "sequential") == 0){
                    strcpy(style, "seq");
                }else{
                    printf("Codigo incorreto, coloque sequential ou parallel\n\n");
                }
                palavras = palavras->proximo;
            }
            if(palavras != NULL){
                palavras = palavras->proximo;
            }
        }
}