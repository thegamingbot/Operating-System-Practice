// Include the required libraries
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>

// Define the macros
#define BufferSize 5

// Global constants
int in = 0, out = 0;
int buffer[BufferSize];

// Function declarations
void* producer(void *params);
void* consumer(void *params);
void printBuffer();

// Main driver function
int main(){
    // Initialize the mutex and semaphores
    pthread_t ptid[BufferSize], ctid[BufferSize];
    // Create threads for producer and consumer
    for(int i = 0; i < BufferSize; i++)
        pthread_create(&ptid[i], NULL, (void *)producer, (void *)&i);
    for(int i = 0; i < BufferSize; i++)
        pthread_create(&ctid[i], NULL, (void *)consumer, (void *)&i);
    // Wait for the threads to complete
    for(int i = 0; i < BufferSize; i++)
        pthread_join(ptid[i], NULL);
    for(int i = 0; i < BufferSize; i++)
        pthread_join(ctid[i], NULL);
    return 0;
}

// A function for the producer
void* producer(void *params){
    // Get a random number in the range of 1 and 10
    int item = rand() % 10 + 1;
    // Add it to the buffer
    buffer[in] = item;
    printf("Producer: %d\tInserted Item: %d\tIndex: %d\n", *((int *)params), item, in);
    printBuffer();
    // Increment the buffer
    // Go around if pointer overflows
    in = (in + 1) % BufferSize;
    sleep(2);
}

// A function for the consumer
void* consumer(void *params){
    // Consume the buffer element
    int item = buffer[out];
    printf("Consumer: %d\tRemoved Item : %d\tIndex: %d\n", *((int *)params), item, out);
    printBuffer();
    // Increment the buffer
    // Go around if pointer overflows
    out = (out + 1) % BufferSize;
    sleep(2);
}

// A function to print the buffer
void printBuffer(){
    printf("Buffer array: ");
    for(int i = 0; i < BufferSize; i++)
        printf("%d ", buffer[i]);
    printf("\n\n");
}