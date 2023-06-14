#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sjf(int processes[], int bursts[], int num_processes) {
    int i, j, min_idx;
    int waiting_time[num_processes], turnaround_time[num_processes];

    for (i = 0; i < num_processes - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < num_processes; j++) {
            if (bursts[j] < bursts[min_idx])
                min_idx = j;
        }
        swap(&bursts[min_idx], &bursts[i]);
        swap(&processes[min_idx], &processes[i]);
    }

  
    waiting_time[0] = 0;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    for (i = 1; i < num_processes; i++) {
        waiting_time[i] = bursts[i - 1] + waiting_time[i - 1];
        total_waiting_time += waiting_time[i];
    }

    for (i = 0; i < num_processes; i++) {
        turnaround_time[i] = bursts[i] + waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }

 
    double average_waiting_time = (double)total_waiting_time / num_processes;
    double average_turnaround_time = (double)total_turnaround_time / num_processes;


    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < num_processes; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i], bursts[i], waiting_time[i], turnaround_time[i]);
    }

    printf("\nAverage Waiting Time: %.2f\n", average_waiting_time);
    printf("Average Turnaround Time: %.2f\n", average_turnaround_time);
}

int main() {
    int processes[] = {0, 1, 2};
    int bursts[] = {2, 4, 8};
    int num_processes = sizeof(processes) / sizeof(processes[0]);

    sjf(processes, bursts, num_processes);

    return 0;
}

