/* 
		Author: Mehmet Şemdin Aktay - 20190702102 
		Date: 26.03.2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define ARRAY_SIZE 2000000 // I decreased it because sometimes I got segmentation fault.
#define SUB_ARRAY_SIZE 1000

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
    
    // Update the array
    for (i = 0; i < ARRAY_SIZE; i += SUB_ARRAY_SIZE) {
        int start_index = i;
        int end_index = i + SUB_ARRAY_SIZE;
        if (end_index > ARRAY_SIZE) {
            end_index = ARRAY_SIZE;
        }
        // Update the subarray
        for (j = start_index; j < end_index; j++) {
            arr[j]++;
        }
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