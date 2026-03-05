#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "input.h"
#include <string.h>
void printar(Node *head){
    while (head != NULL)
    {
        printf("%s", head->texto);
        head = head->proximo;
    }
    
}
void ler_arquivo(int argc, char *argv[]){
    Node *frases = NULL;
    Node *palavras = NULL;

    FILE *arquivo = fopen(argv[1], "r");
    
    if(arquivo == NULL){
        printf("Erro ao abrir arquivo %s\n", argv[1]);
    }else{
        char aux[100];
        while(fgets(aux, sizeof(aux), arquivo) != NULL){
            if(strcmp(aux, "\n") == 0) {
                continue;
            }else{
                inserir_lista(&frases, aux);
                char copia[100];
                
                strcpy(copia, aux);

                char *modificado = strtok(copia, " \n");
                while(modificado != NULL){
                    inserir_lista(&palavras, modificado);
                    modificado = strtok(NULL, " \n");
                }
            }
    }
    }
    input(frases, palavras);
    fclose(arquivo);
}