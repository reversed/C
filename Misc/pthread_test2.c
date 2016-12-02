#include <pthread.h>
#include <stdio.h>

#define N 2

void *thread(void *vargp);
char **ptr; /* Global Variable */

int main()
{
    int i;
    pthread_t tid;
    char *msgs[N] = {
        "Hello from foo",
        "Hello from bar"
    };

    ptr = msgs;
    for (i = 0; i < N; ++i)
    {
        pthread_create(&tid, NULL, thread, (void*)(long)i);
    }
    pthread_exit(NULL);

    return 0;
}

void *thread(void *vargp)
{
    int myid = (long)vargp;
    static int cnt = 0;
    printf("[%d]: %s (cnt=%d)\n", myid, ptr[myid], ++cnt);
    return NULL;
}
