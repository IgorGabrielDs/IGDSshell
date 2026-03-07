#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "lista.h"
#include "main.h"
#include "executar_comandos.h"

void input(Node *palavras){

    if (palavras == NULL){
        return;
    }

    if (strcmp(palavras->texto, "style") == 0){
        tratar_style(palavras);
        return;
    }

    if (strcmp(palavras->texto, "cd") == 0){
        executar_cd(palavras);
        return;
    }

    if (strcmp(palavras->texto, "exit") == 0){
        exit(0);
    }

    executar_comandos(palavras);
}