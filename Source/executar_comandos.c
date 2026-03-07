#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "lista.h"
#include "main.h"

void tratar_style(Node *palavras){

    if (palavras->proximo == NULL){
        printf("\x1b[1mCodigo incompleto, coloque sequential ou parallel\x1b[0m\n");
        return;
    }

    if (strcmp(palavras->proximo->texto, "parallel") == 0){
        strcpy(style, "par");
    }
    else if (strcmp(palavras->proximo->texto, "sequential") == 0){
        strcpy(style, "seq");
    }
    else{
        printf("\x1b[1mCodigo incorreto, coloque sequential ou parallel\x1b[0m\n");
    }
}


void executar_comandos(Node *palavras){
    char *argv[100];
    int i = 0;
    Node *atual = palavras;
    while (atual != NULL && i < 99){
        argv[i] = atual->texto;
        i++;
        atual = atual->proximo;
    }
    argv[i] = NULL;
    if (argv[0] == NULL){
        return;
    }
    pid_t pid = fork();
    if (pid < 0){
        perror("fork");
        return;
    }
    if (pid == 0){
        execvp(argv[0], argv);
        perror("execvp");
        exit(1);
    }else{
        waitpid(pid, NULL, 0);
    }
}

void executar_cd(Node *palavras){
    if (palavras->proximo == NULL){
            printf("\x1b[1mcd: caminho nao informado\x1b[0m\n");
            return;
        }

        if (chdir(palavras->proximo->texto) != 0){
            perror("cd");
        }
        return;
}