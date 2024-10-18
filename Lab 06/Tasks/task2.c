#include <stdio.h>
#include <omp.h>

#define ARRAY_SIZE 5

// Function to compute the sum of an array using tasks
int compute_sum(int *arr, int size) {
    int sum = 0;

    #pragma omp parallel
    {
        int partial_sum = 0;

        #pragma omp for
        for (int i = 0; i < size; i++) {
            partial_sum += arr[i];
        }

        #pragma omp atomic
        sum += partial_sum;
    }

    return sum;
}

// Function to compute the product of an array using tasks
int compute_product(int *arr, int size) {
    int product = 1;

    #pragma omp parallel
    {
        int partial_product = 1;

        #pragma omp for
        for (int i = 0; i < size; i++) {
            partial_product *= arr[i];
        }

        #pragma omp atomic
        product *= partial_product;
    }

    return product;
}

// Function to find the maximum value in an array
int compute_max(int *arr, int size) {
    int max_value = arr[0];

    #pragma omp parallel for
    for (int i = 1; i < size; i++) {
        #pragma omp critical
        {
            if (arr[i] > max_value) {
                max_value = arr[i];
            }
        }
    }

    return max_value;
}

int main() {
    int arr[ARRAY_SIZE] = {1, 2, 3, 4, 5};
    int sum, product, max_value;

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            sum = compute_sum(arr, ARRAY_SIZE);
        }
        #pragma omp section
        {
            product = compute_product(arr, ARRAY_SIZE);
        }
        #pragma omp section
        {
            max_value = compute_max(arr, ARRAY_SIZE);
        }
    }

    // Print the results
    printf("Array: [");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d", arr[i]);
        if (i < ARRAY_SIZE - 1) printf(", ");
    }
    printf("]\n");
    printf("Sum: %d\n", sum);
    printf("Product: %d\n", product);
    printf("Maximum: %d\n", max_value);

    return 0;
}
