#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void input_arquivo(Node *head){
    while (head != NULL){

        char aux[100];
        strcpy(aux, head->texto);

        char *corrigido = strtok(aux, " ");

        while(corrigido != NULL){
            printf("%s\n", corrigido);
            //fazer ação
            corrigido = strtok(NULL, " ");
        }

        head = head->proximo;
    }
}
void input(char *frase){
    char *corrigido = strtok(frase, " ");
    while(corrigido != NULL){
        printf("%s\n", frase);
        //Descobrir a palavra
        corrigido = strtok(NULL, " ");
    }
}