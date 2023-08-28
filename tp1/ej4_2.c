#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char *argv[], char *envp[]) {
    int pid = fork();
    if (pid < 0)
        return 1;

    if (pid == 0) {
        // Hijo P (Produce/Escribe)
        execve("p", argv, envp);
    }

    // Termina el padre
    return 0;
}

/* int main(int argc, char *argv[], char *envp[]) {
    int fds[2]; // pipefd[0] refers to the read end of the pipe.
                // pipefd[1] refers to the write end of the pipe.
    if (pipe(fds) < 0) // Creo un pipe, antes del fork asi ambos procesos lo tienen
        return 1;
    int pid = fork();
    if (pid < 0)
        return 1;

    if (pid == 0) {
        // Hijo C (Consume/Lee)
        close(0); // Cerramos STDIN en padre
        dup(fds[0]); // Dupeamos read end of pipe -> Lo manda a STDIN
        close(fds[0]); // Cerrramos ambos extremos del pipe
        close(fds[1]);

        execve("c", argv, envp);

    } else {
        // Padre P (Produce/Escribe)
        int bg_pid = fork(); // Crear un nuevo proceso para ejecutar 'p' en background
        if (bg_pid == 0) {
            close(1); // Cerramos STDOUT en hijo
            dup(fds[1]); // Dupeamos write end of pipe -> Lo manda a STDOUT
            close(fds[0]); // Cerramos ambos extremos
            close(fds[1]);

            execve("p", argv, envp);
        } else if (bg_pid > 0) {
            // Este es el proceso original del padre, que ahora está libre para hacer otras cosas
            // porque 'p' se está ejecutando en un proceso separado (en background)
            close(fds[0]);
            close(fds[1]);
        } else {
            // fork falló
            return 1;
        }
    }
} */
