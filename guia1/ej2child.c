#include <unistd.h>
#include <stdio.h>

int main() {
    printf("PID: %d\n", getpid());
    // printf("Sleeping 3 seconds..."); Porque si esta este print, no se imprime hasta despues del sleep?
    sleep(3);
}