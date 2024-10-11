#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;
pthread_cond_t cond_var;
int produced_value = 0; // Variable to store the produced value
int item_available = 0;  // Flag to indicate if an item is available

void* producer(void* arg) {
    while (1) {
        int num = rand() % 100 + 1; // Produce a random number

        pthread_mutex_lock(&mutex);
        
        // Produce item
        produced_value = num;
        item_available = 1; // Set flag to indicate item is produced
        printf("Produced: %d\n", produced_value);
        
        // Signal consumer that item is produced
        pthread_cond_signal(&cond_var);
        pthread_mutex_unlock(&mutex);

        sleep(rand() % 2 + 1); // Simulate production time
    }
    return NULL;
}

void* consumer(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        
        // Wait until an item is produced
        while (item_available == 0) {
            printf("Waiting for the producer to produce.....\n");
            pthread_cond_wait(&cond_var, &mutex);
        }
        
        // Consume item
        printf("Consumed: %d\n", produced_value);
        item_available = 0; // Reset flag
        pthread_mutex_unlock(&mutex);

        sleep(rand() % 2 + 1); // Simulate consumption time
    }
    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;

    // Initialize mutex and condition variable
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_var, NULL);

    // Create producer and consumer threads
    pthread_create(&cons_thread, NULL, consumer, NULL);
    pthread_create(&prod_thread, NULL, producer, NULL);

    // Wait for threads to finish (they won't, in this case)
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // Cleanup (won't be reached in this example)
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_var);

    return 0;
}
