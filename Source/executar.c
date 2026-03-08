#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "main.h"
#include "executar.h"
#include "input.h"
#include "lista.h"

pid_t executar_comandos(char **palavras){
    pid_t pid = fork();

    if (pid < 0){
        printf("\x1b[1;37mIgds \x1b[1;32m%s \x1b[1;37m> \x1b[1;31mErro em fork: %s\x1b[0m\n", style, strerror(errno));
        return -1;
    }

    if (pid == 0){
        execvp(palavras[0], palavras);
        printf("\x1b[1;37mIgds \x1b[1;32m%s \x1b[1;37m> \x1b[1;31mErro ao executar comando: %s\x1b[0m\n", style, strerror(errno));
        exit(1);
    }

    return pid;
}

void tratar_style(char **palavras){
    if (palavras[1] == NULL){
        printf("\x1b[1;37mIgds \x1b[1;32m%s \x1b[1;37m> \x1b[1;31mstyle: argumento faltando\x1b[0m\n", style);
        return;
    }

    if (strcmp(palavras[1], "sequential") == 0){
        strcpy(style, "seq");
    }
    else if (strcmp(palavras[1], "parallel") == 0){
        strcpy(style, "par");
    }
    else{
        printf("\x1b[1;37mIgds \x1b[1;32m%s \x1b[1;37m> \x1b[1;31mstyle: modo invalido\x1b[0m\n", style);
    }
}

void executar_cd(char **palavras){
    if (palavras[1] == NULL){
        printf("\x1b[1;37mIgds \x1b[1;32m%s \x1b[1;37m> \x1b[1;31mcd: argumento faltando\x1b[0m\n", style);
        return;
    }

    if (chdir(palavras[1]) != 0){
        printf("\x1b[1;37mIgds \x1b[1;32m%s \x1b[1;37m> \x1b[1;31mErro em cd: %s\x1b[0m\n", style, strerror(errno));
    }
}

void executar_pipe(char *comando){
    char copia[200];
    strcpy(copia, comando);

    char *contexto_pipe;
    char *comando1 = strtok_r(copia, "|", &contexto_pipe);
    char *comando2 = strtok_r(NULL, "|", &contexto_pipe);

    if (comando1 == NULL || comando2 == NULL){
        printf("\x1b[1;37mIgds \x1b[1;32m%s \x1b[1;37m> \x1b[1;31mErro: pipe invalido\x1b[0m\n", style);
        return;
    }

    char **palavras1 = input_palavra(comando1);
    char **palavras2 = input_palavra(comando2);

    if (palavras1 == NULL || palavras1[0] == NULL || palavras2 == NULL || palavras2[0] == NULL){
        printf("\x1b[1;37mIgds \x1b[1;32m%s \x1b[1;37m> \x1b[1;31mErro: comando invalido no pipe\x1b[0m\n", style);
        free_lista(palavras1);
        free_lista(palavras2);
        return;
    }

    int fd[2];
    if (pipe(fd) == -1){
        printf("\x1b[1;37mIgds \x1b[1;32m%s \x1b[1;37m> \x1b[1;31mErro em pipe: %s\x1b[0m\n", style, strerror(errno));
        free_lista(palavras1);
        free_lista(palavras2);
        return;
    }

    pid_t pid1 = fork();
    if (pid1 < 0){
        printf("\x1b[1;37mIgds \x1b[1;32m%s \x1b[1;37m> \x1b[1;31mErro em fork: %s\x1b[0m\n", style, strerror(errno));
        close(fd[0]);
        close(fd[1]);
        free_lista(palavras1);
        free_lista(palavras2);
        return;
    }

    if (pid1 == 0){
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);

        execvp(palavras1[0], palavras1);
        printf("\x1b[1;37mIgds \x1b[1;32m%s \x1b[1;37m> \x1b[1;31mErro ao executar comando: %s\x1b[0m\n", style, strerror(errno));
        exit(1);
    }

    pid_t pid2 = fork();
    if (pid2 < 0){
        printf("\x1b[1;37mIgds \x1b[1;32m%s \x1b[1;37m> \x1b[1;31mErro em fork: %s\x1b[0m\n", style, strerror(errno));
        close(fd[0]);
        close(fd[1]);
        free_lista(palavras1);
        free_lista(palavras2);
        return;
    }

    if (pid2 == 0){
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);

        execvp(palavras2[0], palavras2);
        printf("\x1b[1;37mIgds \x1b[1;32m%s \x1b[1;37m> \x1b[1;31mErro ao executar comando: %s\x1b[0m\n", style, strerror(errno));
        exit(1);
    }

    close(fd[0]);
    close(fd[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    free_lista(palavras1);
    free_lista(palavras2);
}

void executar_redirecionamento(char *comando){
    char copia[200];
    strcpy(copia, comando);

    char *parte_comando = NULL;
    char *arquivo = NULL;
    int tipo = 0;

    if (strstr(copia, ">>") != NULL){
        tipo = 2;
        parte_comando = strtok(copia, ">");
        arquivo = strtok(NULL, ">");
    }
    else if (strchr(copia, '>') != NULL){
        tipo = 1;
        parte_comando = strtok(copia, ">");
        arquivo = strtok(NULL, ">");
    }
    else if (strchr(copia, '<') != NULL){
        tipo = 3;
        parte_comando = strtok(copia, "<");
        arquivo = strtok(NULL, "<");
    }
    else{
        printf("\x1b[1;37mIgds \x1b[1;32m%s \x1b[1;37m> \x1b[1;31mErro: redirecionamento invalido\x1b[0m\n", style);
        return;
    }

    if (parte_comando == NULL || arquivo == NULL){
        printf("\x1b[1;37mIgds \x1b[1;32m%s \x1b[1;37m> \x1b[1;31mErro: redirecionamento invalido\x1b[0m\n", style);
        return;
    }

    char **palavras = input_palavra(parte_comando);
    char **nome_arquivo = input_palavra(arquivo);

    if (palavras == NULL || palavras[0] == NULL || nome_arquivo == NULL || nome_arquivo[0] == NULL){
        printf("\x1b[1;37mIgds \x1b[1;32m%s \x1b[1;37m> \x1b[1;31mErro: comando ou arquivo invalido\x1b[0m\n", style);
        free_lista(palavras);
        free_lista(nome_arquivo);
        return;
    }

    pid_t pid = fork();

    if (pid < 0){
        printf("\x1b[1;37mIgds \x1b[1;32m%s \x1b[1;37m> \x1b[1;31mErro em fork: %s\x1b[0m\n", style, strerror(errno));
        free_lista(palavras);
        free_lista(nome_arquivo);
        return;
    }

    if (pid == 0){
        int fd;

        if (tipo == 1){
            fd = open(nome_arquivo[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        }
        else if (tipo == 2){
            fd = open(nome_arquivo[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
        }
        else{
            fd = open(nome_arquivo[0], O_RDONLY);
        }

        if (fd < 0){
            printf("\x1b[1;37mIgds \x1b[1;32m%s \x1b[1;37m> \x1b[1;31mErro ao abrir arquivo: %s\x1b[0m\n", style, strerror(errno));
            exit(1);
        }

        if (tipo == 1 || tipo == 2){
            dup2(fd, STDOUT_FILENO);
        }
        else{
            dup2(fd, STDIN_FILENO);
        }

        close(fd);

        execvp(palavras[0], palavras);
        printf("\x1b[1;37mIgds \x1b[1;32m%s \x1b[1;37m> \x1b[1;31mErro ao executar comando: %s\x1b[0m\n", style, strerror(errno));
        exit(1);
    }

    waitpid(pid, NULL, 0);

    free_lista(palavras);
    free_lista(nome_arquivo);
}