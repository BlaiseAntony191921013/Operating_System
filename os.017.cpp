#include<stdio.h>

void findWaitingTime(int burst_time[], int n, int quantum_time, int waiting_time[]) {
    int remaining_time[n];
    for (int i = 0; i < n; i++) {
        remaining_time[i] = burst_time[i];
    }

    int time = 0;
    while (1) {
        int all_done = 1;

        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                all_done = 0;

                if (remaining_time[i] > quantum_time) {
                    time += quantum_time;
                    remaining_time[i] -= quantum_time;
                } else {
                    time += remaining_time[i];
                    waiting_time[i] = time - burst_time[i];
                    remaining_time[i] = 0;
                }
            }
        }

        if (all_done)
            break;
    }
}

void findTurnaroundTime(int burst_time[], int n, int waiting_time[], int turnaround_time[]) {
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = burst_time[i] + waiting_time[i];
    }
}

void findAverageTimes(int burst_time[], int n, int quantum_time) {
    int waiting_time[n], turnaround_time[n], total_waiting_time = 0, total_turnaround_time = 0;

    findWaitingTime(burst_time, n, quantum_time, waiting_time);
    findTurnaroundTime(burst_time, n, waiting_time, turnaround_time);

    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];

        printf("P%d\t%d\t\t%d\t\t%d\n", i + 1, burst_time[i], waiting_time[i], turnaround_time[i]);
    }

    float avg_waiting_time = (float) total_waiting_time / n;
    float avg_turnaround_time = (float) total_turnaround_time / n;

    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}

int main() {
    int burst_time[] = {24, 3, 3};
    int num_processes = sizeof(burst_time) / sizeof(burst_time[0]);
    int quantum_time = 4;

    findAverageTimes(burst_time, num_processes, quantum_time);

    return 0;
}


