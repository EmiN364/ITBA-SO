#include <unistd.h>

// ps ax -O "%P"

int main() {
    for (int i = 0; i < 5; i++) {
        if (fork() == 0) {
            if (i != 0)
                return 0;
            break;
        }
    }
    while (1) {
        //
    }
}

/* 

1_ Se quedan esperando al padre. 
 5533     1R pts/0    00:00:21 ./ej3
 5534  5533R pts/0    00:00:21 ./ej3
 5535  5533Z pts/0    00:00:00 [ej3] <defunct>
 5536  5533Z pts/0    00:00:00 [ej3] <defunct>
 5537  5533Z pts/0    00:00:00 [ej3] <defunct>
 5538  5533Z pts/0    00:00:00 [ej3] <defunct>

 From your output we see a "defunct", which means the process has either completed its task or has been corrupted or killed, but its child processes are still running or these parent process is monitoring its child process. To kill this kind of process, kill -9 PID doesn't work. You can try to kill them with this command but it will show this again and again.

2,3_  Todos los hijos que ya habian terminado y estaban en defunct mueren,
el que seguia en el loop queda huerfano, cambia su PPIDS y asciende a proceso padre?

  PID  PPIDS TTY          TIME COMMAND
    1     0S pts/0    00:00:00 bash
 5519     0S pts/1    00:00:00 bash
 5534     1R pts/0    00:00:41 ./ej3
 5541  5519R pts/1    00:00:00 ps ax -O %P

4_ Es el primer proceso que inicia a los demas, xq sino seria imposible crear procesos. Es el padre de todos, como la clase Object en Java

5_ En sistemas operativos Unix, un proceso zombi o "defunct" (difunto) es un proceso que ha completado su ejecución pero aún tiene una entrada en la tabla de procesos​, lo que permite al proceso que lo ha creado leer el estado de su salida. Metafóricamente, el proceso hijo ha muerto pero su "alma" aún no ha sido recogida.
    Un proceso zombi no es lo mismo que un proceso huérfano. Los procesos huérfanos no se convierten en procesos zombis, sino que son adoptados por init (ID del proceso = 1), que espera a su hijo.

 */