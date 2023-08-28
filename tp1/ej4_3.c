#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[], char *envp[]) {
    int pid = fork();
    if (pid < 0)
        return 1;

    if (pid == 0) {
        // Hijo P (Produce/Escribe)

        int fd = open("4_3.txt", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
        close(1); // Cierro stdout
        dup(fd); // me manda fd a stdout
        close(fd);
        execve("p", argv, envp);
    }

    // Termina el padre
    return 0;
}