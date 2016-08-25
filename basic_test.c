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
        //tmp = execve(command, parameters, 0); /* execute command */ }
        //tmp = execve(comando, &parametro, 0); /* execute command */
        //printf("comando > %s\n", comando);
        //printf("parametro > %s\n", parametro);
        //tmp = execve(comando, parametro, 0); /* execute command */
        //tmp = execve(comando, parametro, newenviron);
        tmp = execve(comando[0], comando, newenviron);
        printf ("%d", tmp);
    }
    return 0;
}

int main(int argc, char * const argv[], char * const envp[]) {
    char line_tudo[MAX_LENGTH];
    int processo, i = 0;
    char * tmp, * tmp1;
    char **tokens = malloc(100 * sizeof(char*));
    
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
            printf("entrou rodeveja\n");

            //tmp = strtok (NULL, " \n\t\r");
            //strcpy(param[0], tmp);
            tmp = strtok(NULL, DELIM);
            while(tmp != NULL) {
                tokens[i] = malloc(strlen(tmp) * sizeof(char));
                strcpy(tokens[i], tmp);
                i++;
                tmp = strtok(NULL, DELIM);
            }
            tokens[i] = NULL;

            processo = rodeveja(tokens);
            //tmp1 = tmp;
            
            //tmp = strtok (NULL, " \n\t\r");
            //printf("%s\n", tmp);
            //printf("%s\n", tmp1);
            //processo = rodeveja(tmp1);
            //processo = rodeveja(param);
            //if (tmp == NULL) {
            //    processo = rodeveja(tmp1, 0);
            //}
            //else {
            //    processo = rodeveja(tmp1, tmp);
            //}

        }
        else system(line_tudo);
    }

    return 0;
}
