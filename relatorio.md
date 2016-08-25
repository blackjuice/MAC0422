*Alunos: Leonardo Daneu Lopes (8516816) e Lucas Sung Jun Hong (8124329)*

### MAC0422 - Sistemas Operacionais
## Relatório
# mac422shell

<div style="page-break-after: always;"></div>

# Conteúdo

1) Introdução
2) Proteção 000 e 777
 2.1) protegepracaramba ()
 2.2) liberageral ()
3) Função: rodeveja ()
4) Função: rode ()
5) Funções auxiliares
6) Bibliografia

<div style="page-break-after: always;"></div>

# 1) Introdução
Para o funcionamento deste EP, temos as seguintes funções:

```cpp

int protegepracaramba   ( char *filename );
int liberageral         ( char *filename );
int rodeveja            ( char **comando );
int rode                ( char **comando );
void free_tokens        ( char **tokens );

```

# 2) Proteção 000 e 777

## 2.1) protegepracaramba ()
Para a proteção 000, chama-se a função:

```cpp
int protegepracaramba ( char *filename );
```

Em que usa-se o `chmod` como:

```cpp
return syscall(SYS_chmod, filename, 0);
```

Um exemplo de execução, usando um arquivo `test`, em que inicialmente tem o estado:

```cpp
-rwxr-xr-x 1 lucassjhong bcc 6744 Ago 25 19:00 test
```

Fazendo a chamada:

```cpp
$ protegepracaramba test
```

Teremos:

```cpp
---------- 1 lucassjhong bcc 6744 Aug 25 19:04 test
```

## 2.2) liberageral ()
Para a proteção 000, chama-se a função:

```cpp
int liberageral ( char *filename );
```

Em que usa-se o `chmod` como:

```cpp
return syscall(SYS_chmod, filename, 0777);
```

Usando um arquivo `test`, similar ao teste anterior, fazendo a chamada:

```cpp
$ liberageral test
```

Teremos:

```cpp
-rwxrwxrwx 1 lucassjhong bcc 6744 Ago 25 19:26 test
```

<div style="page-break-after: always;"></div>

# 3) Função: rodeveja ()

Após a declaração de um processo `pid_t pid = fork();`, verifica-se:

```cpp
if (pid == 0) {
        tmp = execve(comando[0], comando, newenviron);
}
else if (pid == -1) {
        perror("wait()");
    }
    else {
        if (wait(&status) != -1) {
            if (WIFEXITED(status)) {
                printf("programa %s retorna com código %d\n", comando[0], WEXITSTATUS(status));
            }
            else if (WIFSIGNALED(status)) {
                printf("I hate Química\n");
            }
        } 
    } 
```

Se o processo é igual a zero, temos um processo filho e executaremos o processo através do `execve()`, em que passamos no primeiro argumento o comando, em seguida os argumentos do comando, sendo ele um array de strings e por último environment, nesse caso, {NULL};

Se o processo é -1, trataremos a entrada como um erro;

Caso contrário, teremos um processo pai e faremos a verificação: 

`if (WIFEXITED(status))`: se o processo filho retorna um valor maior que zero, imprimimos esse resultado, sendo que foi executado sem problemas;

`else if (WIFSIGNALED(status))`: caso contrário, foi recebido um sinal do sistema e imprimimos uma mensagem de erro.

<div style="page-break-after: always;"></div>

# 4) Função: rode ()

<div style="page-break-after: always;"></div>

# 5) Funções auxiliares

Usamos uma função auxiliar: `void free_tokens ( char **tokens );`, em que recebe um array de strings e libera-se a memória alocada pela `int main()`:

        void free_tokens (char **tokens) {
            int i;
            for (i = 0; i < BUFFSIZE; i++)
                free(tokens[i]);
        }

Aqui, `BUFFSIZE` = 50 pois assume-se que os argumentos de entrada, por exemplo `<caminho do arquivo>` ou `<caminho do programa>`, não passará de mais de 50 caracteres.

<div style="page-break-after: always;"></div>

# 6) Bibliografia

http://stackoverflow.com/

http://man7.org/linux/man-pages/man2/

http://www.tutorialspoint.com/cprogramming/

http://paca.ime.usp.br/

http://pubs.opengroup.org/onlinepubs/7908799/xsh/unistd.h.html

http://www.die.net/

http://users.sosdg.org/~qiyong/mxr/blurb.html