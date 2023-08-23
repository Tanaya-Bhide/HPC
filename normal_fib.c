#include <stdio.h>
#include <time.h>

int sequentialFibonacci(int n) {
    if (n <= 1)
        return n;
    else
        return sequentialFibonacci(n - 1) + sequentialFibonacci(n - 2);
}

int main() {
    int n = 40;
    
    clock_t start_time = clock(); // Record the starting time
    
    int result = sequentialFibonacci(n);
    
    clock_t end_time = clock();   // Record the ending time
    double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    
    printf("Sequential Fibonacci(%d) = %d\n", n, result);
    printf("Execution time: %f seconds\n", execution_time);
    
    return 0;
}
