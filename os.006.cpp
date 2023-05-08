#include <stdio.h>

#define P 3 // number of processes
#define R 3 // number of resource instances

int main() {
    int max[P][R] = {{3, 6, 8}, {4, 3, 3}, {3, 4, 4}}; // maximum demand matrix
    int allocation[P][R] = {{3, 3, 3}, {2, 0, 3}, {1, 2, 4}}; // allocation matrix
    int available[R] = {1, 2, 0}; // available resources

    int need[P][R]; // need matrix
    int finish[P] = {0}; // array to keep track of finished processes
    int deadlock = 1; // flag to indicate if deadlock has occurred

    // calculate need matrix
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // check if there is a process that can be finished
    while (deadlock) {
        deadlock = 0;

        for (int i = 0; i < P; i++) {
            // check if the process has not finished yet and if it can be finished
            if (!finish[i]) {
                int can_finish = 1;

                for (int j = 0; j < R; j++) {
                    if (need[i][j] > available[j]) {
                        can_finish = 0;
                        break;
                    }
                }

                // if the process can be finished, release its resources
                if (can_finish) {
                    finish[i] = 1;
                    deadlock = 1;

                    for (int j = 0; j < R; j++) {
                        available[j] += allocation[i][j];
                    }
                }
            }
        }
    }

    // check if all processes have finished
    for (int i = 0; i < P; i++) {
        if (!finish[i]) {
            printf("Deadlock detected!\n");
            printf("The deadlocked processes are: ");
            for (int j = 0; j < P; j++) {
                if (!finish[j]) {
                    printf("%d ", j);
                }
            }
            printf("\n");
            return 0;
        }
    }

    printf("No deadlock detected.\n");
    return 0;
}