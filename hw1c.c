/* 
		Author: Mehmet Şemdin Aktay - 20190702102 
		Date: 26.03.2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define ARRAY_SIZE 2000000 // I decreased it because sometimes I got segmentation fault.
#define SUB_ARRAY_SIZE 1000
#define NUM_THREADS ARRAY_SIZE / SUB_ARRAY_SIZE

// Struct for passing arguments to the thread function
typedef struct {
    int start_index;
    int end_index;
    int *arr;
} ThreadArgs;

// Thread function for updating the subarray
void* updateSubarray(void* arg) {
    ThreadArgs* args = (ThreadArgs*) arg;
    int i;
    
    // Update the subarray
    for (i = args->start_index; i < args->end_index; i++) {
        args->arr[i]++;
    }
    
    // Exit the thread
    pthread_exit(NULL);
}

int main() {
    int *arr = (int*) malloc(ARRAY_SIZE * sizeof(int));
    int i, j;
    pthread_t threads[NUM_THREADS];
    ThreadArgs args[NUM_THREADS];
    
    // Initialize the array with random positive integers
    for (i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = rand() % 1000;
    }
    
    // Start the timer
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);
    
    // Create the threads and pass arguments
    for (i = 0; i < NUM_THREADS; i++) {
        args[i].start_index = i * SUB_ARRAY_SIZE;
        args[i].end_index = args[i].start_index + SUB_ARRAY_SIZE;
        args[i].arr = arr;
        pthread_create(&threads[i], NULL, updateSubarray, &args[i]);
    }
    
    // Join the threads
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // Stop the timer
    gettimeofday(&end_time, NULL);
    
    // Calculate the total time of execution
    long seconds = end_time.tv_sec - start_time.tv_sec;
    long microseconds = end_time.tv_usec - start_time.tv_usec;
    double total_time = seconds + microseconds / 1e6;
    
    // Print the updated array
    printf("Updated array:\n");
    for (i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    // Print the total time of execution
    printf("Total time: %f seconds\n", total_time);
    
    // Free the dynamically allocated memory
    free(arr);
    
    return 0;
}