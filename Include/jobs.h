#ifndef JOBS_H
#define JOBS_H

#include <sys/types.h>

typedef struct {
    int id;
    pid_t pid;
    int ativo;
    char comando[200];
} Job;

extern Job jobs[100];
extern int prox_job_id;

void adicionar_job(pid_t pid, char *comando);
void trazer_fg(int id);
void verificar_jobs();

#endif