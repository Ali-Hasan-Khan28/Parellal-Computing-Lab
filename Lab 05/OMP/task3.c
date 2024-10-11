#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define ARRAY_SIZE 5

int main() {
    int array[ARRAY_SIZE];
    int jk = 0;

    // Seed the random number generator
    srand(time(NULL));

    // Initialize the array with random values
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % 100; // Random values between 0 and 99
    }

    // Print the array (optional)
    printf("Array: ");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    // Calculate the sum using OpenMP
    #pragma omp parallel for reduction(+:sum)
    {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        jk += array[i];
    }
    }

    // Print the result
    printf("Sum of array elements: %d\n", jk);

    return 0;
}
