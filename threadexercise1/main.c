#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "threading.h"

#define NUM_THREADS 5

int main() {
    shared_counter = (int *)malloc(sizeof(int));
    if (shared_counter == NULL) {
        perror("Failed to allocate memory for shared counter");
        exit(EXIT_FAILURE);
    }
    *shared_counter = 0;
    if (pthread_mutex_init(&lock, NULL) != 0) {
        perror("Mutex initialization failed");
        free(shared_counter);
        exit(EXIT_FAILURE);
    }
    pthread_t threads[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        int *thread_id = (int *)malloc(sizeof(int));
        if (thread_id == NULL) {
            perror("Failed to allocate memory for thread ID");
            free(shared_counter);
            exit(EXIT_FAILURE);
        }
        *thread_id = i;
        if (pthread_create(&threads[i], NULL, thread_function, thread_id) != 0) {
            perror("Thread creation failed");
            free(thread_id);
            free(shared_counter);
            exit(EXIT_FAILURE);
        }
   }
   for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&lock);
    free(shared_counter);
    return 0;
}
