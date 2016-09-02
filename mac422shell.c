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
#include <sys/stat.h>

#define DELIM       " \n\0"
#define DELIM_SPACE "\n\0"
#define MAX_LENGTH  70
#define BUFF_SIZE   50

/*-------------------------------------------------*/
/*-------------------FUNCOES-----------------------*/
/*-------------------------------------------------*/
int protegepracaramba ( char *filename ) {
    return chmod(filename, 0);
}

int liberageral ( char *filename ) {
    return chmod(filename, 0777);    
}

int rodeveja (char **comando) {
    int         status;
    char *const newenviron[] = { NULL };
    pid_t pid = fork();

    // processo filho
    if (pid == 0) execve(comando[0], comando, newenviron);
    
    // erro no fork()
    else if (pid == -1) {
        perror("Erro");
        exit(0);
    }
    // processo pai
    else {
        if (wait(&status) != -1) {
            if (WIFEXITED(status)) printf("programa %s retorna com código %d\n", comando[0], WEXITSTATUS(status));
            else if (WIFSIGNALED(status)) printf("pid %ld não detectou número do signal %d\n", (long)pid, WTERMSIG(status));
        }
    }
    return 0;
}

void rode ( char **comando) {
    char *const newenviron[] = { NULL };
    pid_t pid = fork();

    // processo filho
<<<<<<< HEAD
    if (pid == 0 ) {
        close(pid);
        execve(comando[0], comando, newenviron);
    }
    
=======
    if (pid == 0 )  {
        //close(pid);
        execve(comando[0], comando, newenviron);
    }

>>>>>>> origin/master
    // erro no fork()
    else if (pid == -1) {
        perror("Erro");
        exit(0);
    }
}


/*-------------------------------------------------*/
/*-------------FUNCOES AUXILIARES------------------*/
/*-------------------------------------------------*/
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
    char    * tmp;
    char    *parametro[BUFF_SIZE];

    while (1) {
        printf("$ ");

        if (!fgets(line_tudo, MAX_LENGTH, stdin)) break;
        
        tmp = strtok (line_tudo, DELIM);

        /* CONDICOES */
        // protegepracaramba <caminho do arquivo>
        if (!strcmp("protegepracaramba", tmp)) {
            tmp         = strtok (NULL, DELIM);
            protegepracaramba(tmp);
        }

        // liberageral <caminho do arquivo>
        if (!strcmp("liberageral", tmp)) {
            tmp         = strtok (NULL, DELIM);
            liberageral(tmp);
        }

        // rodeveja <caminho do programa>
        if (!strcmp("rodeveja", tmp)) {
            tmp = strtok(NULL, DELIM_SPACE);
            separa_token (tmp, parametro);
            rodeveja(parametro);
        }

        // rode <caminho do programa> 
        if (!strcmp("rode", tmp)) {
            tmp = strtok(NULL, DELIM_SPACE);
            separa_token (tmp, parametro);
            rode(parametro);
        }
    }
    return 0;
}
