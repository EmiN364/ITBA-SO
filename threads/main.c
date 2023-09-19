#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sched.h>
#include <semaphore.h>

int sem_init(sem_t *sem, int pshared, unsigned int value);
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                    void *(*start_routine) (void *), void *arg);

int cien = 0;
sem_t sem;

void *thread_function(void *arg) {
    // sem_wait(&sem);
    int aux = cien;
    sched_yield();
    cien = aux + 10;
    // sem_post(&sem);
}

/* void *thread_function(void *arg) {
    while (cien < 100) {
        sched_yield();
        sem_wait(&sem);
        if (cien<100) cien++;
        sem_post(&sem);
    }
} */


int main(int argc, char *argv[]) {

    sem_init(&sem, 0, 1);

    pthread_t my_threads[10];

    for (int i = 0; i < 10; i++) {
        pthread_create(&my_threads[i], NULL, thread_function, NULL);
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(my_threads[i], NULL);
    }

    sem_destroy(&sem);

    printf("cien = %d\n", cien); // cien = 100 (o "cerca de 100")

    return 0;
}