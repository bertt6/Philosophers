
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>

void *myThreadFun(void *vargp)
{
    sleep(1);
    printf("Selamlar\n");
    return NULL;
}

int main()
{
    pthread_t thread_id;
    printf("Before thread\n");
    pthread_create(&thread_id, NULL, myThreadFun, NULL);
    pthread_join(thread_id, NULL);
    printf("After Thread\n");
    exit(1);
}

