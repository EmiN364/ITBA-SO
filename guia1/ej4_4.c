#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[], char *envp[]) {
    
    int fd = open("4_3.txt", O_RDONLY);
    if (fd < 0)
        return -1;
    close(0); // Cierro STDIN
    dup(fd); // Copio fd a 0
    close(fd); // Cierro fd
    execve("c", argv, envp);

    return 0;
}

/* Modifique la resolución del inciso 3 del ejercicio 2, de manera tal que el proceso padre ejecute c, pero que en lugar de leer de stdin lea de un archivo. */