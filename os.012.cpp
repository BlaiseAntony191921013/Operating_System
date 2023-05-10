#include <stdio.h>
#include <stdbool.h>

#define MAX_PARTITIONS 6
#define MAX_PROCESSES 5

int main() {
    int partitions[MAX_PARTITIONS] = {300, 600, 350, 200, 750, 125};
    int processes[MAX_PROCESSES] = {115, 500, 358, 200, 375};
    int allocation[MAX_PROCESSES] = {-1, -1, -1, -1, -1};
    bool allocated[MAX_PARTITIONS];

    // Initialize allocated array to false
    for (int i = 0; i < MAX_PARTITIONS; i++) {
        allocated[i] = false;
    }

    // Allocate memory blocks to each process using the best-fit algorithm
    for (int i = 0; i < MAX_PROCESSES; i++) {
        int best_index = -1;
        for (int j = 0; j < MAX_PARTITIONS; j++) {
            if (!allocated[j] && processes[i] <= partitions[j]) {
                if (best_index == -1 || partitions[j] < partitions[best_index]) {
                    best_index = j;
                }
            }
        }
        if (best_index != -1) {
            allocation[i] = best_index;
            allocated[best_index] = true;
        }
    }

    // Print the memory allocation for each process
    printf("Process\tMemory Size\tPartition\n");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        printf("%d\t%d KB\t\t", i+1, processes[i]);
        if (allocation[i] != -1) {
            printf("%d KB\n", partitions[allocation[i]]);
        } else {
            printf("Not allocated\n");
        }
    }

    return 0;
}