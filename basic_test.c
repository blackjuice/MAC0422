#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/syscall.h>
#include "sys/stat.h"
#define TRUE  1
#define FALSE 0

#define DELIM " \n"
#define MAX_LENGTH 100
#define BUFFSIZE 20

/*  */
int protegepracaramba( char *filename );
int liberageral ( char *filename );
int rodeveja (char **comando);

int protegepracaramba( char *filename ) {
    return syscall(SYS_chmod, filename, 0);
}

int liberageral ( char *filename ) {
    return syscall(SYS_chmod, filename, 0777);    
}

//int rodeveja (char * comando, char * parametro[], char *filename, char * env[]) {
int rodeveja (char **comando) {

    //execve( filename, argv, envp);
    int status;
    int tmp;

    //char *newargv[] = 
    char *const parametro[] = { NULL };
    char *const newenviron[] = { NULL };

    if (fork() != 0){
        /* Parent code. */
         wait(&status);
    } 
    else {
        /* Child code. */
        printf ("%s", comando[0]);
        tmp = execve(comando[0], comando, newenviron);
        printf("programa %s retorna %d\n", comando[0], tmp);
        printf ("%d", tmp);
    }
    return 0;
}

int main(int argc, char * const argv[], char * const envp[]) 
{
    char line_tudo[MAX_LENGTH];
    int processo, i, j;
    char * tmp, * tmp1;
    char **tokens;
    char * const rapidinho[] = {NULL};

    while (1) {
        printf("$ ");
        if (!fgets(line_tudo, MAX_LENGTH, stdin)) break;
        
        tmp = strtok (line_tudo, DELIM);
        if (!strcmp("protegepracaramba", tmp)) {
            printf("entrou protegepracaramba\n");
            tmp = strtok (NULL, DELIM);
            processo = protegepracaramba(tmp);
        }
        if (!strcmp("liberageral", tmp)) {
            printf("entrou liberageral\n");
            tmp = strtok (NULL, DELIM);
            processo = liberageral(tmp);
        }
        if (!strcmp("rodeveja", tmp)) {
            i = 0;  
            tokens = malloc(50 * sizeof(char*));
            tmp = strtok(NULL, DELIM);

            while(tmp != NULL) {
                tokens[i] = malloc(strlen(tmp) * sizeof(char));
                strcpy(tokens[i], tmp);
                i++;
                tmp = strtok(NULL, DELIM);
            }
            tokens[i] = NULL;
            processo = rodeveja(tokens);

            for (i = 0; i < 50; i++)
                free(tokens[i]);
            
        }
        //else 
          //  system(line_tudo);
    }

    return 0;
}
