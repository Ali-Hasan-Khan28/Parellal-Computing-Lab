#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Number of cars (threads)
#define NUM_CARS 4

// Number of checkpoints
#define NUM_CHECKPOINTS 3

// Barrier for synchronization
pthread_barrier_t barrier;

// Function executed by each car (thread)
void* car_thread(void* arg) {
    int car_id = *((int*)arg);
    
    for (int checkpoint = 1; checkpoint <= NUM_CHECKPOINTS; checkpoint++) {
        // Simulate some time taken to reach the checkpoint
        usleep(rand() % 1000000); // Random delay for realism
        
        // Print progress of the car
        printf("Car %d reached checkpoint %d\n", car_id, checkpoint);
        
        // Wait at the barrier until all cars reach this checkpoint
        pthread_barrier_wait(&barrier);
    }
    
    return NULL;
}

int main() {
    srand(time(NULL)); // Seed for random number generation

    // Initialize the barrier to synchronize NUM_CARS threads
    pthread_barrier_init(&barrier, NULL, NUM_CARS);
    
    // Create threads representing cars
    pthread_t cars[NUM_CARS];
    int car_ids[NUM_CARS];
    
    for (int i = 0; i < NUM_CARS; i++) {
        car_ids[i] = i + 1;
        pthread_create(&cars[i], NULL, car_thread, &car_ids[i]);
    }

    // Wait for all car threads to finish the race
    for (int i = 0; i < NUM_CARS; i++) {
        pthread_join(cars[i], NULL);
    }

    // Destroy the barrier after use
    pthread_barrier_destroy(&barrier);
    
    printf("Race completed!\n");
    
    return 0;
}