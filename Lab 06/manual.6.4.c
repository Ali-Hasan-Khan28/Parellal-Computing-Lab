#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
int summation(int *array, int N)
{
    if (N == 0)
        return 0;
    else if (N == 1)
        return *array;
    int half = N / 2;
    return summation(array, half) + summation(array + half,
                                              N - half);
}
int summation_1(int *A, int N)
{
    if (N == 0)
        return 0;
    else if (N == 1)
        return *A;
    int half = N / 2;
    int x, y;
    omp_set_num_threads(4);
#pragma omp parallel
#pragma omp single
    {
#pragma omp task shared(x)
        x = summation_1(A, half);
#pragma omp task shared(y)
        y = summation_1(A + half, N - half);
#pragma omp taskwait
         x += y;
    }
    return x;
}
int main()
{
    int sz = 500;
    int A[sz];
    for (int i = 0; i < sz; i++)
    {
        A[i] = rand() % 10;
    }
    printf("%d\n", summation(A, sz));
#pragma omp parallel num_threads(4) private(tid)
    {
#pragma omp single
        {
            tid = omp_get_thread_num();
            printf("Hello world from (%d) \n", tid);
            printf("Sum = %d by %d \n", fib(A, sz), tid);
        }
    }
    // printf("%d\n", summation_1(A,sz));
    return 0;
}
