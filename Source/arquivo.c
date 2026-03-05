#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "input.h"


void free_arquivo(Node **head){
    Node *atual = *head;
    Node *temp;

    while(atual != NULL){
        temp = atual;
        atual = atual->proximo;
        free(temp);
    }

    *head = NULL;
}
void ler_arquivo(int argc, char *argv[]){
    Node *palavras = NULL;

    FILE *arquivo = fopen(argv[1], "r");
    
    if(arquivo == NULL){
        printf("\x1b[1mErro ao abrir arquivo %s \x1b[0m\n", argv[1]);
    }else{
        char aux[100];
        printf("%s:\n", argv[1]);
        while(fgets(aux, sizeof(aux), arquivo) != NULL){
            
            if(strcmp(aux, "\n") == 0) {
                continue;
            }

            printf("%s", aux);

            char copia[100];
            strcpy(copia, aux);

            char *modificado = strtok(copia, " \n");

            while(modificado != NULL){
                inserir_lista(&palavras, modificado);
                modificado = strtok(NULL, " \n");
    }
    }
    printf("\n");
    input(palavras);
    free_arquivo(&palavras);
    fclose(arquivo);
}
}