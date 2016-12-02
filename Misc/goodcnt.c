#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

void *thread(void *vargp);

volatile int cnt = 0;
sem_t mutex;

int main(int argc, char** argv)
{
    int niters;
    pthread_t tid1, tid2;

    if (argc != 2)
    {
        printf("usage: %s <niters>\n", argv[0]);
        return 0;
    }

    sem_init(&mutex, 0, 1); // mutex = 1

    niters = atoi(argv[1]);

    pthread_create(&tid1, NULL, thread, &niters);
    pthread_create(&tid2, NULL, thread, &niters);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    if (cnt != (2 * niters))
        printf("BOOM! cnt = %d\n", cnt);
    else
        printf("OK cnt = %d\n", cnt);

    return 0;
}

void *thread(void *vargp)
{
    int i, niters = *((int*)vargp);

    for (i = 0; i < niters; ++i)
    {
        sem_wait(&mutex);
        cnt++;
        sem_post(&mutex);
    }

    return NULL;
}
