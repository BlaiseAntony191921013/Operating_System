#include <stdio.h>
#include <stdbool.h>

#define MAX_PARTITIONS 5
#define MAX_PROCESSES 5

// Structure to represent a memory partition
struct MemoryPartition {
    int size;
    bool allocated;
};

// Structure to represent a process
struct Process {
    int size;
    int partitionIndex;
};

// Function to allocate memory blocks to processes using the worst-fit algorithm
void worstFit(struct MemoryPartition partitions[], int numPartitions, struct Process processes[], int numProcesses) {
    for (int i = 0; i < numProcesses; i++) {
        int maxIndex = -1;

        // Find the partition with the maximum size that can accommodate the process
        for (int j = 0; j < numPartitions; j++) {
            if (!partitions[j].allocated && partitions[j].size >= processes[i].size) {
                if (maxIndex == -1 || partitions[j].size > partitions[maxIndex].size) {
                    maxIndex = j;
                }
            }
        }

        // Allocate the process to the partition with the maximum size
        if (maxIndex != -1) {
            partitions[maxIndex].allocated = true;
            processes[i].partitionIndex = maxIndex;
        }
    }
}

int main() {
    struct MemoryPartition partitions[MAX_PARTITIONS] = {
        {40, false},
        {10, false},
        {30, false},
        {60, false}
    };

    struct Process processes[MAX_PROCESSES] = {
        {100, -1},
        {50, -1},
        {30, -1},
        {120, -1},
        {35, -1}
    };

    int numPartitions = sizeof(partitions) / sizeof(partitions[0]);
    int numProcesses = sizeof(processes) / sizeof(processes[0]);

    worstFit(partitions, numPartitions, processes, numProcesses);

    printf("Process\t\tPartition\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("%d\t\t", processes[i].size);
        if (processes[i].partitionIndex != -1) {
            printf("%d (%d KB)\n", processes[i].partitionIndex, partitions[processes[i].partitionIndex].size);
        } else {
            printf("Not allocated\n");
        }
    }

    return 0;
}

