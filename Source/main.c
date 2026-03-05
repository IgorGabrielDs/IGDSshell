#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"
#include "input.h"
#include "main.h"

char style[4] = "seq";

int main(int argc, char *argv[]) {

    if (argc > 2) {
        printf("\x1b[1mErro ao tentar abrir arquivo %s\x1b[0m\n\n", argv[1]);
    }

    if (argc == 2) {
        ler_arquivo(argc, argv);
    }

    while (1) {
        Node *palavras = NULL;

        printf("igds %s> ", style);
        fflush(stdout);

        char aux[100];


        if (fgets(aux, sizeof(aux), stdin) == NULL) {
            printf("\n");
            break;
        }

        if (strcmp(aux, "\n") == 0) {
            continue;
        }
        aux[strcspn(aux, "\n")] = '\0';

        char copia[100];

        strcpy(copia, aux);

        char *modificado = strtok(copia, " \n");
        while (modificado != NULL) {
            inserir_lista(&palavras, modificado);
            modificado = strtok(NULL, " \n");
        }
        input(palavras);
        free_arquivo(&palavras);
    }

    return 0;
}