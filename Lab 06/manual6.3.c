#include <stdio.h>
#include <omp.h>
int summation(int x)
{
    return x + 2;
}
int product(int x)
{
    return x * 2;
}
int sub(int x)
{
    return x - 2;
}
int main()
{
    int x;
    scanf("%d", &x);
#pragma omp parallel sections num_threads(1)
    {
#pragma omp section
        printf("%d \n", summation(x));
#pragma omp section
        printf("%d \n", product(x));
#pragma omp section
        printf("%d \n", sub(x));
    }
    return 0;
}