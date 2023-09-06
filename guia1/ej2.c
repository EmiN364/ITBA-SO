#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char * argv[], char *envp[]) {
    int pids[10];
    for (int i = 0; i < 10 ; i++) {
        int pid = fork();
        if (pid < 0)
            return 1;
        
        if (pid == 0) {
            // HIJO
            /* printf("PID: %d\n", getpid());
            sleep(3);
            return 0; */
            execve("ej2child", argv, envp);
        } else {
            // PADRE
            pids[i] = pid;
        }
    }
    for (int i = 0; i < 10; i++) {
        int stat;
        waitpid(pids[i], &stat, 0);
    }
}