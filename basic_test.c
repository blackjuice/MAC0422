#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/syscall.h>
#include "sys/stat.h"
#define TRUE  1
#define FALSE 0
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

#define MAX_LENGTH 100

int protegepracaramba( char *filename );

int protegepracaramba( char *filename ) {
    int tmp = syscall(SYS_chmod, filename, 0);
    //printf ("%d\n", tmp);
    //printf ("%s\n", (char *)(filename));
    return tmp;
}

int main() {
    char line_tudo[MAX_LENGTH];
    int proc;
    //char str[] ="protegepracaramba /GitHub/MAC0422_Operating_Systems/test";
    char * tmp;

    while (1) {
        printf("$ ");
        if (!fgets(line_tudo, MAX_LENGTH, stdin)) break;
        
        tmp = strtok (line_tudo, " \n");
        if (!strcmp("protegepracaramba", tmp)) {
            tmp = strtok (NULL, " \n");
            proc = protegepracaramba(tmp);
        }
        else system(line_tudo);
    }

    return 0;
}
