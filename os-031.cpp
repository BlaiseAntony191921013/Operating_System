#include <stdio.h>
#include <stdlib.h>

// Function to sort an array in ascending order
void sort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

// Function to calculate the absolute difference between two numbers
int absDiff(int a, int b) {
    return (a > b) ? (a - b) : (b - a);
}

// Function to simulate CSCAN disk scheduling algorithm
void cscan(int tracks[], int n, int head, int maxTrack) {
    int i, j, k, distance = 0;
    int* visited = (int*)calloc(n, sizeof(int));

    // Sort the tracks in ascending order
    sort(tracks, n);

    // Find the index of head in the sorted tracks
    for (i = 0; i < n; i++) {
        if (tracks[i] >= head) {
            break;
        }
    }

    // Perform CSCAN algorithm
    printf("Head Movement: %d", head);
    for (j = i; j < n; j++) {
        printf(" -> %d", tracks[j]);
        distance += absDiff(head, tracks[j]);
        head = tracks[j];
        visited[j] = 1;
    }
    printf(" -> %d", maxTrack);

    for (k = 0; k < i; k++) {
        if (!visited[k]) {
            printf(" -> %d", tracks[k]);
            distance += absDiff(head, tracks[k]);
            head = tracks[k];
        }
    }

    printf("\nAverage Head Movement: %.2f\n", (float)distance / n);

    free(visited);
}

int main() {
    int tracks[] = {55, 58, 60, 70, 18};
    int n = sizeof(tracks) / sizeof(tracks[0]);
    int head = 50;
    int maxTrack = 99;

    cscan(tracks, n, head, maxTrack);

    return 0;
}

