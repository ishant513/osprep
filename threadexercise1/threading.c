#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "threading.h"

int *shared_counter;
pthread_mutex_t lock;

void *thread_function(void *arg) {
    int *thread_id = (int *)arg;
    pthread_mutex_lock(&lock);
    (*shared_counter)++;
    printf("Thread %d: Shared Counter = %d\n", *thread_id, *shared_counter);
    pthread_mutex_unlock(&lock);
    free(thread_id);

    return NULL;
}
