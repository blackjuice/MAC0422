#include <stdio.h>
#include <string.h>

int main()
{
    char * comando;
    char * parametro;
    char * const rapidinho[] = {NULL};

    char line[18] = "hello world bitch";
    printf("%s\n", line);
    comando = strtok(line, " \n");
    printf("> %s\n", comando);

    comando = strtok(NULL, "");
    printf(">> %s\n", comando);
    
    printf("rapidinho = %s\n", *rapidinho);

    printf("%c\n", parametro[0]);
    //printf("%s\n", strcpy(*rapidinho, parametro));
    return 0;
}