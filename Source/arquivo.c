#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "input.h"
#include "main.h"

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
    FILE *arquivo = fopen(argv[1], "r");
    if(arquivo == NULL){
        printf("\x1b[1mIgds \x1b[32m%s\x1b[0m> Erro ao abrir arquivo \"%s\"\n", style, argv[1]);
        return;
    }
    char aux[100];
    while(fgets(aux, sizeof(aux), arquivo) != NULL){
        Node *palavras = NULL;
        if(strcmp(aux, "\n") == 0){
            continue;
        }
        aux[strcspn(aux, "\n")] = '\0';
        if(strcmp(aux, "") == 0){
            continue;
        }
        char copia[100];
        strcpy(copia, aux);
        char *modificado = strtok(copia, " ");
        while(modificado != NULL){
            inserir_lista(&palavras, modificado);
            modificado = strtok(NULL, " ");
        }
        input(palavras);
        free_arquivo(&palavras);
    }
    printf("\n");
    fclose(arquivo);
}