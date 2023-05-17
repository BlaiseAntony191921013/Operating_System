#include <stdio.h>

#define MAX_PARTITIONS 6
#define MAX_PROCESSES 5

// Structure to represent memory partitions
typedef struct {
    int size;
    int allocated;
} MemoryPartition;

// Structure to represent processes
typedef struct {
    int size;
    int allocated_partition;
} Process;

// Function to find the worst-fit partition for a process
int findWorstFitPartition(MemoryPartition partitions[], int num_partitions, int process_size) {
    int index = -1;
    int max_size = -1;

    for (int i = 0; i < num_partitions; i++) {
        if (!partitions[i].allocated && partitions[i].size >= process_size) {
            if (partitions[i].size > max_size) {
                max_size = partitions[i].size;
                index = i;
            }
        }
    }

    return index;
}

// Function to allocate memory partitions to processes using the worst-fit algorithm
void allocateMemory(Process processes[], MemoryPartition partitions[], int num_processes, int num_partitions) {
    for (int i = 0; i < num_processes; i++) {
        int index = findWorstFitPartition(partitions, num_partitions, processes[i].size);

        if (index != -1) {
            partitions[index].allocated = 1;
            processes[i].allocated_partition = index;
        } else {
            processes[i].allocated_partition = -1;
        }
    }
}

// Function to display the allocation results
void displayAllocation(Process processes[], MemoryPartition partitions[], int num_processes) {
    printf("Process\tProcess Size\tPartition\n");
    for (int i = 0; i < num_processes; i++) {
        printf("%d\t%d KB\t\t", i + 1, processes[i].size);
        if (processes[i].allocated_partition != -1) {
            printf("%d (%d KB)\n", processes[i].allocated_partition + 1, partitions[processes[i].allocated_partition].size);
        } else {
            printf("Not Allocated\n");
        }
    }
}

int main() {
    MemoryPartition partitions[MAX_PARTITIONS] = {
        {300, 0},
        {600, 0},
        {350, 0},
        {200, 0},
        {750, 0},
        {125, 0}
    };

    Process processes[MAX_PROCESSES] = {
        {115, -1},
        {500, -1},
        {358, -1},
        {200, -1},
        {375, -1}
    };

    allocateMemory(processes, partitions, MAX_PROCESSES, MAX_PARTITIONS);
    displayAllocation(processes, partitions, MAX_PROCESSES);

    return 0;
}