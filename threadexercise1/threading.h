#ifndef THREAD_FUNCTION_H
#define THREAD_FUNCTION_H

#include <pthread.h>

extern int *shared_counter;
extern pthread_mutex_t lock;
void *thread_function(void *arg);

#endif 
