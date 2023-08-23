#include <stdio.h>
#include <omp.h>
#include <time.h>
#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int front = 0, rear = 0;
int count = 0;

// Function to add data to the buffer
void produce(int data)
{
#pragma omp critical
    {
        if (count < BUFFER_SIZE)
        {
            buffer[rear] = data;
            rear = (rear + 1) % BUFFER_SIZE;
            count++;
            printf("Produced: %d\n", data);
        }
        else
        {
            printf("Buffer full. Producer waiting.\n");
        }
    }
}

// Function to consume data from the buffer
void consume()
{
#pragma omp critical
    {
        if (count > 0)
        {
            int data = buffer[front];
            front = (front + 1) % BUFFER_SIZE;
            count--;
            printf("Consumed: %d\n", data);
        }
        else
        {
            printf("Buffer empty. Consumer waiting.\n");
        }
    }
}

int main()
{
    clock_t start_clock, end_clock;

    start_clock = clock();
#pragma omp parallel sections
    {
#pragma omp section
        {
            for (int i = 1; i <= 100; i++)
            {
                produce(i);
            }
        }

#pragma omp section
        {
            for (int i = 1; i <= 100; i++)
            {
                consume();
            }
        }
    }
    end_clock = clock();

    double cpu_time_used = ((double)(end_clock - start_clock)) / CLOCKS_PER_SEC;
    printf("Total execution time: %f seconds\n", cpu_time_used);

    return 0;
}