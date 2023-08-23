#include <stdio.h>
#include <omp.h>
#include <time.h>

int fibonacci(int n) {
    if (n <= 1)
        return n;

    int fib1, fib2;

    #pragma omp task shared(fib1)
    fib1 = fibonacci(n - 1);

    #pragma omp task shared(fib2)
    fib2 = fibonacci(n - 2);

    #pragma omp taskwait
    return fib1 + fib2;
}

int main() {
    int n = 40;
    int result;
    clock_t start_time = clock();  
    #pragma omp parallel
    {
        #pragma omp single
        result = fibonacci(n);
    }
    clock_t end_time = clock();    
    double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    
    printf("Fibonacci(%d) = %d\n", n, result);
    printf("Execution time: %f seconds\n", execution_time);
    return 0;
}
