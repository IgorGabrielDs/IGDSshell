#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "main.h"

void input(Node *frases, Node *palavras){
        while (palavras != NULL){
            if(strcmp(palavras->texto, "style") == 0){
                if(palavras->proximo == NULL){
                    printf("Codigo incompleto, coloque sequential ou parallel\n");
                    break;
                }
                palavras = palavras->proximo;

                if(strcmp(palavras->texto, "parallel") == 0){
                    strcpy(style, "par");
                }else if(strcmp(palavras->texto, "sequential") == 0){
                    strcpy(style, "seq");
                }else{
                    printf("Codigo incorreto, coloque sequential ou parallel\n");
                }
            }
            palavras = palavras->proximo;
        }
}