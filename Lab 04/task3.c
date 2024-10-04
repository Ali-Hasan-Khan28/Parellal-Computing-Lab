#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MATRIX_SIZE 4

// Matrices A, B, and C
int A[MATRIX_SIZE][MATRIX_SIZE];
int B[MATRIX_SIZE][MATRIX_SIZE];
int C[MATRIX_SIZE][MATRIX_SIZE];

// Mutex to protect access to the result matrix C
pthread_mutex_t mutex;

// Barrier to ensure synchronization of row calculations
pthread_barrier_t barrier;

// Function to perform matrix multiplication for a specific row
void* multiply_row(void* arg) {
    int row = *((int*)arg);

    pthread_mutex_lock(&mutex);
    for (int col = 0; col < MATRIX_SIZE; col++) {
        int sum = 0;
        for (int k = 0; k < MATRIX_SIZE; k++) {
            sum += A[row][k] * B[k][col];
        }

        // Lock mutex to protect shared matrix C
        C[row][col] = sum;
    }
    pthread_mutex_unlock(&mutex);

    // Wait for all threads to finish their row calculations
    pthread_barrier_wait(&barrier);

    return NULL;
}

// Function to generate a random matrix
void generate_random_matrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            matrix[i][j] = rand() % 10 + 1; // Random numbers between 1 and 10
        }
    }
}

// Function to print a matrix
void print_matrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    srand(time(NULL)); // Seed for random number generation

    // Generate random matrices A and B
    generate_random_matrix(A);
    generate_random_matrix(B);

    // Initialize the mutex and barrier
    pthread_mutex_init(&mutex, NULL);
    pthread_barrier_init(&barrier, NULL, MATRIX_SIZE);

    // Print the input matrices
    printf("Matrix A:\n");
    print_matrix(A);
    printf("\nMatrix B:\n");
    print_matrix(B);

    // Create threads for each row of the result matrix
    pthread_t threads[MATRIX_SIZE];
    int row_indices[MATRIX_SIZE];

    for (int i = 0; i < MATRIX_SIZE; i++) {
        row_indices[i] = i;
        pthread_create(&threads[i], NULL, multiply_row, &row_indices[i]);
    }

    // Wait for all threads to complete
    for (int i = 0; i < MATRIX_SIZE; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the mutex and barrier
    pthread_mutex_destroy(&mutex);
    pthread_barrier_destroy(&barrier);

    // Print the result matrix
    printf("\nResult Matrix C:\n");
    print_matrix(C);

    return 0;
}