#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "jobs.h"
#include "main.h"

Job jobs[100];
int prox_job_id = 1;

void adicionar_job(pid_t pid, char *comando){
    for (int i = 0; i < 100; i++){
        if (jobs[i].ativo == 0){
            jobs[i].id = prox_job_id;
            jobs[i].pid = pid;
            jobs[i].ativo = 1;
            strcpy(jobs[i].comando, comando);

            printf("[%d] %d\n", jobs[i].id, jobs[i].pid);

            prox_job_id++;
            return;
        }
    }

    printf("\x1b[1;37mIgds \x1b[1;32m%s \x1b[1;37m> \x1b[1;31mErro: limite de jobs atingido\x1b[0m\n", style);
}

void trazer_fg(int id){
    for (int i = 0; i < 100; i++){
        if (jobs[i].ativo == 1 && jobs[i].id == id){
            waitpid(jobs[i].pid, NULL, 0);
            jobs[i].ativo = 0;
            return;
        }
    }

    printf("\x1b[1;37mIgds \x1b[1;32m%s \x1b[1;37m> \x1b[1;31mfg: job nao encontrado\x1b[0m\n", style);
}

void verificar_jobs(){
    for (int i = 0; i < 100; i++){
        if (jobs[i].ativo == 1){
            pid_t resultado = waitpid(jobs[i].pid, NULL, WNOHANG);

            if (resultado > 0){
                jobs[i].ativo = 0;
            }
        }
    }
}