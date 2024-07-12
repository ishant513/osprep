#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int count = 0;

// Mutex and Condition variables
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t buffer_not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer_not_empty = PTHREAD_COND_INITIALIZER;

// Producer function
void* producer(void* arg) {
    int i = 0;
    while (1) {
        pthread_mutex_lock(&mutex);
        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&buffer_not_full, &mutex);
        }
        buffer[count] = i;
        printf("Producer produced: %d\n", i);
        count++;
        i++;
        pthread_cond_signal(&buffer_not_empty);
        pthread_mutex_unlock(&mutex);
        sleep(1);  // Simulate time taken to produce an item
    }
    return NULL;
}

// Consumer function
void* consumer(void* arg) {
    int id = *((int*)arg);
    while (1) {
        pthread_mutex_lock(&mutex);
        while (count == 0) {
            pthread_cond_wait(&buffer_not_empty, &mutex);
        }
        count--;
        printf("Consumer %d consumed: %d\n", id, buffer[count]);
        pthread_cond_signal(&buffer_not_full);
        pthread_mutex_unlock(&mutex);
        sleep(1 + id);  // Simulate time taken to consume an item
    }
    return NULL;
}

int main() {
    pthread_t prod, cons1, cons2;
    int id1 = 1, id2 = 2;

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons1, NULL, consumer, &id1);
    pthread_create(&cons2, NULL, consumer, &id2);

    pthread_join(prod, NULL);
    pthread_join(cons1, NULL);
    pthread_join(cons2, NULL);

    return 0;
}

