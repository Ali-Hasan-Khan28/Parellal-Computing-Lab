#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Shared data
int value = 0;          // The produced value
int ready = 0;          // Flag indicating if the value is ready

// Mutex and conditional variable
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

// Consumer function - waits for the producer to signal that data is ready
void* function2(void* arg) {
    pthread_mutex_lock(&lock);  // Acquire the lock
    
    // Wait until the producer signals the condition (value is ready)
    while (ready == 0) {
        printf("Function2: Waiting for the value...\n");
        pthread_cond_wait(&cond, &lock);  // Wait for the signal
    }
    
    // Once signaled, consume the value
    printf("Function2: Read the value = %d\n", value);
    
    pthread_mutex_unlock(&lock);  // Release the lock
    return NULL;
}

// Producer function - produces a value and signals the consumer
void* function1(void* arg) {
    pthread_mutex_lock(&lock);  // Acquire the lock
    
    // Produce a value
    value = 42;  
    ready = 1;   // Set flag to indicate the value is ready
    printf("Function1: Wrote the value: %d\n", value);
    
    // Signal the consumer that data is ready
    pthread_cond_signal(&cond);  
    
    pthread_mutex_unlock(&lock);  // Release the lock
    return NULL;
}

int main() {
    pthread_t funct1, funct2;

    // Create producer and consumer threads
    pthread_create(&funct2, NULL, function2, NULL);
    pthread_create(&funct1, NULL, function1, NULL);

    // Wait for both threads to finish
    pthread_join(funct1, NULL);
    pthread_join(funct2, NULL);

    // Clean up
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);

    return 0;
}
