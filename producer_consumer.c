#include <stdio.h>
#include <time.h>
#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int front = 0, rear = 0;
int count = 0;

// Function to add data to the buffer
void produce(int data) {
    if (count < BUFFER_SIZE) {
        buffer[rear] = data;
        rear = (rear + 1) % BUFFER_SIZE;
        count++;
        printf("Produced: %d\n", data);
    } else {
        printf("Buffer full. Producer waiting.\n");
    }
}

// Function to consume data from the buffer
void consume() {
    if (count > 0) {
        int data = buffer[front];
        front = (front + 1) % BUFFER_SIZE;
        count--;
        printf("Consumed: %d\n", data);
    } else {
        printf("Buffer empty. Consumer waiting.\n");
    }
}

int main() {
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    for (int i = 1; i <= 100; i++) {
        produce(i);
    }
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken for producing: %f seconds\n", cpu_time_used);

    start = clock();
    for (int i = 1; i <= 100; i++) {
        consume();
    }
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken for consuming: %f seconds\n", cpu_time_used);

    return 0;
}