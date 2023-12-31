#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

/* Modifique la resolución del inciso 3 del ejercicio 2, de manera tal que el proceso padre ejecute p y c (fork y exec) conectando el 
stdout de p al stdin de c utilizando un pipe (pipe). */

int main(int argc, char *argv[], char *envp[]) {
    int fds[2]; // fds[0] refers to the read end of the pipe.
                // fds[1] refers to the write end of the pipe.
    if (pipe(fds) < 0) // Creo un pipe, antes del fork asi ambos procesos lo tienen
        return 1;
    int pid = fork();
    if (pid < 0)
        return 1;

    if (pid == 0) {
        // HIJO P (Produce/Escribe)
        close(1); // Cerramos STDOUT en hijo
        dup(fds[1]); // Dupeamos write end of pipe -> Lo manda a STDOUT
        close(fds[0]); // Cerramos ambos extremos
        close(fds[1]);

        execve("p", argv, envp);
    } else {
        // Padre C (Consume/Lee)
        close(0); // Cerramos STDIN en padre
        dup(fds[0]); // Dupeamos read end of pipe -> Lo manda a STDIN
        close(fds[0]); // Cerrramos ambos extremos del pipe
        close(fds[1]);

        execve("c", argv, envp);
    }
}