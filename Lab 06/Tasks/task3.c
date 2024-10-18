#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Recursive function to calculate Fibonacci number
int fibonacci(int n) {
    if (n <= 1) return n;
    
    int x, y;
    
    // Create tasks for the two recursive calls
    #pragma omp task shared(x)
    x = fibonacci(n - 1);
    
    #pragma omp task shared(y)
    y = fibonacci(n - 2);
    
    // Wait for all tasks to finish before returning
    #pragma omp taskwait
    return x + y;
}

int main() {
    int n;

    // Input validation
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    printf("Fibonacci series up to %d:\n", n);

    // Use a parallel region to calculate Fibonacci numbers
    #pragma omp parallel
    {
        #pragma omp single
        {
            for (int i = 1; i <= n; i++) {
                int result = fibonacci(i);
                #pragma omp critical
                {
                    printf("%d", result);
                    if (i < n) printf(", ");
                }
            }
        }
    }

    printf("\n");
    return 0;
}
