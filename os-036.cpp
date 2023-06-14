#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

int abs_diff(int a, int b) {
    return abs(a - b);
}

int find_closest_track(int tracks[], int num_tracks, int head_pos, bool visited[]) {
    int min_diff = INT_MAX;
    int closest_track = -1;
    
    for (int i = 0; i < num_tracks; i++) {
        if (!visited[i] && abs_diff(tracks[i], head_pos) < min_diff) {
            min_diff = abs_diff(tracks[i], head_pos);
            closest_track = i;
        }
    }
    
    return closest_track;
}

void sstf(int tracks[], int num_tracks, int start_pos) {
    bool visited[num_tracks];
    for (int i = 0; i < num_tracks; i++) {
        visited[i] = false;
    }
    
    int total_movement = 0;
    int head_pos = start_pos;
    
    printf("Head Movement:\n%d ", head_pos);
    visited[head_pos] = true;
    
    for (int i = 0; i < num_tracks - 1; i++) {
        int closest_track = find_closest_track(tracks, num_tracks, head_pos, visited);
        visited[closest_track] = true;
        total_movement += abs_diff(tracks[closest_track], head_pos);
        head_pos = tracks[closest_track];
        printf("%d ", head_pos);
    }
    
    printf("\nTotal Head Movement: %d\n", total_movement);
    printf("Average Head Movement: %.2f\n", (float)total_movement / num_tracks);
}

int main() {
    int tracks[] = {55, 58, 60, 70, 18};
    int num_tracks = sizeof(tracks) / sizeof(tracks[0]);
    int start_pos = 50; // Starting position of the head

    printf("Track Positions: ");
    for (int i = 0; i < num_tracks; i++) {
        printf("%d ", tracks[i]);
    }
    printf("\nStarting Position: %d\n", start_pos);
    
    sstf(tracks, num_tracks, start_pos);

    return 0;
}

