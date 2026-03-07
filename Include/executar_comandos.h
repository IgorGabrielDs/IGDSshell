#ifndef EXECUTAR_COMANDOS_H
#define EXECUTAR_COMANDOS_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "lista.h"
#include "main.h"

void executar_comandos(Node *palavras);
void executar_cd(Node *palavras);
void tratar_style(Node *palavras);
#endif