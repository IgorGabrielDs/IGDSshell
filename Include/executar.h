#ifndef EXECUTAR_H
#define EXECUTAR_H

#include <sys/types.h>

pid_t executar_comandos(char **palavras);
void tratar_style(char **palavras);
void executar_cd(char **palavras);
void executar_pipe(char *comando);
void executar_redirecionamento(char *comando);

#endif