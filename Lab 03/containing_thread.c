#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int *array;
int array_size;
int even_count[4];  // Array to hold counts from each thread

void* count_even_numbers(void* arg) {
    int thread_id = (int)(long)arg;
    int start = (array_size / 4) * thread_id;  // Assuming 4 threads
    int end = (thread_id == 3) ? array_size : (array_size / 4) * (thread_id + 1); // Last thread handles remainder
    printf("****************************************************************\n");
    printf("P Thread ID :: %d  ",thread_id);
    printf("Starting :: %d  ",start);
    printf("Ending :: %d  ",end);
    printf("\n");
    int local_count = 0;
    for (int i = start; i < end; i++) {
        if (array[i] % 2 == 0) {
            local_count++;
        }
    }

    even_count[thread_id] = local_count;  // Store local count in the global array
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <array_size>\n", argv[0]);
        return 1;
    }

    array_size = atoi(argv[1]);
    array = (int*)malloc(array_size * sizeof(int));

    // Initialize the array with random numbers
    for (int i = 0; i < array_size; i++) {
        array[i] = rand() % 100;  // Random numbers between 0 and 99
    }

    pthread_t threads[4];  // Using 4 threads

    // Create threads
    for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, count_even_numbers, (void*)(long)i);
    }

    // Wait for threads to finish
    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    // Combine results from all threads
    int total_even_count = 0;
    for (int i = 0; i < 4; i++) {
        total_even_count += even_count[i];
    }

    printf("Total even numbers in the array: %d\n", total_even_count);

    // Clean up
    free(array);
    return 0;
}
