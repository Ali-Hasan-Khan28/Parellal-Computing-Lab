#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int *array1, *array2, *result;
int array_size, num_threads;

void* add_arrays(void* arg) {
    int thread_id = (int)(long)arg;
    int start = (array_size / num_threads) * thread_id;
    int end = (thread_id == num_threads - 1) ? array_size : (array_size / num_threads) * (thread_id + 1);
    printf("****************************************************************\n");
    printf("P Thread ID :: %d  ",thread_id);
    printf("Starting :: %d  ",start);
    printf("Ending :: %d  ",end);
    printf("\n");

    for (int i = start; i < end; i++) {
        result[i] = array1[i] + array2[i];
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <array_size> <num_threads>\n", argv[0]);
        return 1;
    }

    array_size = atoi(argv[1]);
    num_threads = atoi(argv[2]);

    array1 = (int*)malloc(array_size * sizeof(int));
    array2 = (int*)malloc(array_size * sizeof(int));
    result = (int*)malloc(array_size * sizeof(int));

    // Initialize arrays with some values
    for (int i = 0; i < array_size; i++) {
        array1[i] = i;
        array2[i] = i * 2;
    }
    printf("Array1\n");
        // Initialize arrays with some values
    for (int i = 0; i < array_size; i++) {
        printf("%d ", array1[i]);
    }
    printf("\nArray2\n");
        // Initialize arrays with some values
    for (int i = 0; i < array_size; i++) {
        printf("%d ", array2[i]);
    }
    printf("\n");
    pthread_t threads[num_threads];

    // Create threads
    for (int i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, add_arrays, (void*)(long)i);
    }

    // Wait for threads to complete
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Print result (optional)
    printf("Result array:\n");
    for (int i = 0; i < array_size; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    // Clean up
    free(array1);
    free(array2);
    free(result);

    return 0;
}
