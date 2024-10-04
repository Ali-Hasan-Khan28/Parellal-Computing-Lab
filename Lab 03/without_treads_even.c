#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <array_size>\n", argv[0]);
        return 1;
    }

    int array_size = atoi(argv[1]);
    int *array = (int*)malloc(array_size * sizeof(int));
    int even_count = 0;

    // Initialize the array with random numbers
    for (int i = 0; i < array_size; i++) {
        array[i] = rand() % 100;  // Random numbers between 0 and 99
    }
    // Initialize the array with random numbers
    for (int i = 0; i < array_size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");


    // Count even numbers
    for (int i = 0; i < array_size; i++) {
        if (array[i] % 2 == 0) {
            even_count++;
        }
    }

    printf("Total even numbers in the array: %d\n", even_count);

    // Clean up
    free(array);
    return 0;
}
