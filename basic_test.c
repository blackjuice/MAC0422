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
#define BUFFSIZE    20

/*-------------------------------------------------*/
/*-----------DECLARACAO DAS FUNCOES----------------*/
/*-------------------------------------------------*/
int protegepracaramba   ( char *filename );
int liberageral         ( char *filename );
int rodeveja            ( char **comando );
void free_tokens        ( char **tokens );

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

    // processo pai
    if (fork() != 0){
         wait(&status);
    } 
    // processo filho
    else {
        tmp = execve(comando[0], comando, newenviron);
        printf("programa %s retorna %d\n", comando[0], tmp);
        printf("%d", tmp);
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
}

/*-------------------------------------------------*/
/*----------------------MAIN-----------------------*/
/*-------------------------------------------------*/
int main () {
    char    line_tudo[MAX_LENGTH];
    int     processo, i, j;
    char    * tmp, * tmp1;
    char    **tokens;

    while (1) {
        printf("$ ");

        if (!fgets(line_tudo, MAX_LENGTH, stdin)) break;
        
        tmp = strtok (line_tudo, DELIM);

        /* CONDICOES */
        /* protegepracaramba <caminho do arquivo> */
        if (!strcmp("protegepracaramba", tmp)) {
            tmp         = strtok (NULL, DELIM);
            processo    = protegepracaramba(tmp);
        }

        /* liberageral <caminho do arquivo> */
        if (!strcmp("liberageral", tmp)) {
            tmp         = strtok (NULL, DELIM);
            processo    = liberageral(tmp);
        }

        /* rodeveja <caminho do programa> */
        if (!strcmp("rodeveja", tmp)) {
            tokens  = malloc(BUFFSIZE * sizeof(char*));
            tmp     = strtok(NULL, DELIM);

            for (i = 0; tmp != NULL; i++) {
                tokens[i]   = malloc(strlen(tmp) * sizeof(char));
                strcpy(tokens[i], tmp);
                tmp         = strtok(NULL, DELIM);
            }
            tokens[i]   = NULL;
            processo    = rodeveja(tokens);

            free_tokens(tokens);
        }
        //else 
          //  system(line_tudo);
    }
    return 0;
}