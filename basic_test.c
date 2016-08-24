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

int protegepracaramba( char *filename );
int liberageral ( char *filename );

int protegepracaramba( char *filename ) {
    return syscall(SYS_chmod, filename, 0);
}

int liberageral ( char *filename ) {
    return syscall(SYS_chmod, filename, 0777);    
}

int main() {
    char line_tudo[MAX_LENGTH];
    int processo;
    char * tmp;

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
        else system(line_tudo);
    }

    return 0;
}
