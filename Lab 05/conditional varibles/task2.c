#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;
pthread_cond_t cond_var;
int current_road = 0; // 0 for Road A, 1 for Road B



void* roadA(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        
        // Wait until the light is green for Road A
        while (current_road != 0) {
            pthread_cond_wait(&cond_var, &mutex);
        }
        
        // Green light for Road A
        printf("Traffic Light: Green for Road A, Red for Road B\n");
        printf("Road A: Green light! Cars passing...\n");
        printf("Road B: Red light! Cars not passing...\n");
        // Simulate cars passing for a short duration
        sleep(2);
        
        // Switch light
        current_road = 1; // Change to Road B
        pthread_cond_signal(&cond_var); // Signal all threads
        pthread_mutex_unlock(&mutex);
        
        // Wait a bit before the next cycle
        sleep(15);
    }
    return NULL;
}

void* roadB(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        
        // Wait until the light is green for Road B
        while (current_road != 1) {
            pthread_cond_wait(&cond_var, &mutex);
        }
        
        // Green light for Road B
        printf("Traffic Light: Green for Road B, Red for Road A\n");
        printf("Road B: Green light! Cars passing...\n");
        printf("Road A: Red light! Cars not passing...\n");
        // Simulate cars passing for a short duration
        sleep(2);
        
        // Switch light
        current_road = 0; // Change to Road A
        pthread_cond_signal(&cond_var); // Signal all threads
        pthread_mutex_unlock(&mutex);
        
        // Wait a bit before the next cycle
        sleep(15);
    }
    return NULL;
}

int main() {
    pthread_t threadA, threadB;

    // Initialize mutex and condition variable
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_var, NULL);

    // Create threads for Road A and Road B
    pthread_create(&threadA, NULL, roadA, NULL);
    pthread_create(&threadB, NULL, roadB, NULL);

    // Wait for threads to finish (they won't in this case)
    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);

    // Cleanup (won't be reached in this example)
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_var);

    return 0;
}
