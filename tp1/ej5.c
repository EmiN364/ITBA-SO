/* Modifique la resolución del inciso 3 del ejercicio 2, de manera tal que el proceso padre ejecute 2 programas de forma secuencial 
considerando 3 escenarios posibles:
a. INCONDICIONAL, primero ejecuta un proceso y cuando termina ejecuta el otro.
b. AND, si el primer proceso falla (exit status != 0), NO se ejecuta el segundo
c. OR, si el primer proceso termina satisfactoriamente (exit status == 0), NO se ejecuta el segundo
Puede utilizar los programas true.c y false.c para hacer pruebas. (hint: man true, man false)
(wait) */

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

#define INCONDICIONAL 1
#define AND 2
#define OR 3

#define METHOD AND

int main(int argc, char * argv[], char *envp[]) {
    int pids[2];
    int pid = fork();
    if (pid < 0)
        return 1;
    
    if (pid == 0) {
        // HIJO
        execve("false", argv, envp);
    } else {
        // PADRE
        int stat;
        waitpid(pid, &stat, 0);
        int shouldExecute = 0;
        switch( METHOD ) {
            case INCONDICIONAL:
                shouldExecute = 1;
                break;
            case AND:
                if (stat == 0)
                    shouldExecute = 1;
                break;
            case OR:
                if (stat != 0)
                    shouldExecute = 1;
                break;
        }
        if (shouldExecute) {
            int pid2 = fork();
            if (pid2 < 0)
                return 1;

            if (pid2 == 0)
                execve("true", argv, envp);
            else
                waitpid(pid2, &stat, 0);
        }
    }
}