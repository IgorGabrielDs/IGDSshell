#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "inserir_lista.h"

void ler_arquivo(int argc, char *argv[], Node **head){
    for(int i=1;i<argc;i++){
        FILE *arquivo = fopen(argv[i], "r");
        if(arquivo == NULL){
            printf("Erro ao abrir arquivo %s\n", argv[i]);
            continue;
        }
        char aux[100];
        while(fscanf(arquivo, "%s", aux) == 1){
            printf("%s\n", aux);
        }
        fclose(arquivo);
    }
}