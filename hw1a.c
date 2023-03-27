/* 
		Author: Mehmet Şemdin Aktay - 20190702102 
		Date: 26.03.2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>

#define ARRAY_SIZE 2000000 // I decreased it because sometimes I got segmentation fault.
#define SUB_ARRAY_SIZE 1000
#define NUM_THREADS ARRAY_SIZE / SUB_ARRAY_SIZE

int main() {
    int *arr = (int*) malloc(ARRAY_SIZE * sizeof(int));
    int i, j;
    
    // Initialize the array with random positive integers
    for (i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = rand() % 1000;
    }
    
    // Start the timer
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);
    
    // Create the child processes
    int pid, status;
    for (i = 0; i < NUM_THREADS; i++) {
        pid = fork();
        if (pid == 0) {
            // This is the child process
            for (j = i; j < ARRAY_SIZE; j += NUM_THREADS) {
                int start_index = j;
                int end_index = j + SUB_ARRAY_SIZE;
                if (end_index > ARRAY_SIZE) {
                    end_index = ARRAY_SIZE;
                }
                // Update the subarray
                for (int k = start_index; k < end_index; k++) {
                    arr[k]++;
                }
            }
            exit(0);
        }
    }
    
    // Wait for all child processes to finish
    for (i = 0; i < NUM_THREADS; i++) {
        wait(&status);
    }
    
    // Stop the timer
    gettimeofday(&end_time, NULL);
    
    // Calculate the total time of execution
    long seconds = end_time.tv_sec - start_time.tv_sec;
    long microseconds = end_time.tv_usec - start_time.tv_usec;
    double total_time = seconds + microseconds / 1e6;
    
    // Print the updated array and total time of execution
    for (i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("Total time: %f seconds\n", total_time);
    
    // Free the dynamically allocated memory
    free(arr);
    
    return 0;
}