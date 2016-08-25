#include <stdio.h>
#include <unistd.h>

int main (void) {
    char * const argv[] = {"/bin/ls", "-la", NULL};
    char * const envp[] = {NULL};
    int rc = execve (argv[0], argv, envp);
    return rc;
}