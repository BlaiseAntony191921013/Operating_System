#include <stdio.h>


void priorityScheduling(int processes[], int n, int burstTime[], int priority[]) 
{
    int waitingTime[n], turnaroundTime[n], completionTime[n], totalWaitTime = 0, totalTurnaroundTime = 0;
    waitingTime[0] = 0;
    completionTime[0] = burstTime[0];
    turnaroundTime[0] = completionTime[0];
    

    for (int i = 1; i < n; i++) {
        completionTime[i] = completionTime[i-1] + burstTime[i];
    }


    for (int i = 1; i < n; i++) {
        waitingTime[i] = completionTime[i-1] - priority[i-1] + waitingTime[i-1];
        if (waitingTime[i] < 0) {
            waitingTime[i] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = burstTime[i] + waitingTime[i];
    }


    for (int i = 0; i < n; i++) {
        totalWaitTime += waitingTime[i];
        totalTurnaroundTime += turnaroundTime[i];
    }


    printf("\nProcess\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], burstTime[i], priority[i], waitingTime[i], turnaroundTime[i]);
    }
    printf("\nAverage Waiting Time: %.2f", (float)totalWaitTime/n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)totalTurnaroundTime/n);
}


int main() 
{
    int n = 3;
    int processes[] = {1, 2, 3};
    int burstTime[] = {30, 5, 12};
    int priority[] = {2, 1, 3};
    
    priorityScheduling(processes, n, burstTime, priority);
    
    return 0;
}

