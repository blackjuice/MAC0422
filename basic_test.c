/*
 * EP1 - MAC0422 - SISTEMAS OPERACIONAIS
 * alunos:  Leonardo Daneu Lopes;   no.USP: 8516816
 *          Lucas Sung Jun Hong;    no.USP: 8124329
 *
*/ 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/syscall.h>
#include "sys/stat.h"
#define TRUE        1
#define FALSE       0
#define DELIM       " \n"
#define MAX_LENGTH  100
#define BUFFSIZE    50

/*-------------------------------------------------*/
/*-----------DECLARACAO DAS FUNCOES----------------*/
/*-------------------------------------------------*/


/*-------------------------------------------------*/
/*-------------------FUNCOES-----------------------*/
/*-------------------------------------------------*/
int protegepracaramba ( char *filename ) {
    return syscall(SYS_chmod, filename, 0);
}

int liberageral ( char *filename ) {
    return syscall(SYS_chmod, filename, 0777);    
}

int rodeveja (char **comando) {
    int         status;
    int         tmp;
    char *const newenviron[] = { NULL };
    pid_t pid = fork();

    // processo filho
    if (pid == 0) {
        tmp = execve(comando[0], comando, newenviron);
    }
    // erro no fork()
    else if (pid == -1) {
        perror("Erro");
        exit(0);
    }
    // processo pai
    else {
        if (wait(&status) != -1) {
            if (WIFEXITED(status)) { 
                printf("programa %s retorna com código %d\n", comando[0], WEXITSTATUS(status));
            }
            else if (WIFSIGNALED(status)) {
                printf("pid %ld não detectou número do signal %d\n", (long)pid, WTERMSIG(status));
            }
        }
    } 
    return 0;
}

int rode ( char **comando) {
    int         status;
    int         tmp;
    char *const newenviron[] = { NULL };
    pid_t pid = fork();

    // processo filho
    if (pid == 0 ) {
        printf("entrou\n");
        tmp = execve(comando[0], comando, newenviron);
    }
    // erro no fork()
    else if (pid == -1) {
        perror("Erro");
        exit(0);
    }
    return 0;
}


/*-------------------------------------------------*/
/*-------------FUNCOES AUXILIARES------------------*/
/*-------------------------------------------------*/
void free_tokens (char **tokens) {
    int i;
    for (i = 0; i < BUFFSIZE; i++)
        free(tokens[i]);
    free(tokens);
}

void separa_token (char *comando, char *parametro[]){
    int i;
    char *tmp;
        tmp = strtok(comando, DELIM);   
    for(i = 0; tmp != NULL; i++) {
        parametro[i] = tmp;
        tmp = strtok (NULL, DELIM);
    }
    parametro[i] = NULL;
}

/*-------------------------------------------------*/
/*----------------------MAIN-----------------------*/
/*-------------------------------------------------*/
int main () {
    char    line_tudo[MAX_LENGTH];
    int     processo, i, j;
    char    * tmp, * tmp1;
    char    **tokens;
    char *argv[30];

    while (1) {
        printf("$ ");

        if (!fgets(line_tudo, MAX_LENGTH, stdin)) break;
        
        tmp = strtok (line_tudo, DELIM);

        /* CONDICOES */
        // protegepracaramba <caminho do arquivo>
        if (!strcmp("protegepracaramba", tmp)) {
            tmp         = strtok (NULL, DELIM);
            processo    = protegepracaramba(tmp);
        }

        // liberageral <caminho do arquivo>
        if (!strcmp("liberageral", tmp)) {
            tmp         = strtok (NULL, DELIM);
            processo    = liberageral(tmp);
        }

        // rodeveja <caminho do programa>
        if (!strcmp("rodeveja", tmp)) {
            tmp = strtok(NULL, DELIM);
            separa_token (tmp, argv);
            processo    = rodeveja(argv);

        }

        // rode <caminho do programa> 
        if (!strcmp("rode", tmp)) {

            tmp = strtok(NULL, DELIM);
            separa_token (tmp, argv);
            processo    = rode(argv);
        }
    }
    return 0;
}
