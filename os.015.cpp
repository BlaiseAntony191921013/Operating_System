#include<stdio.h>
#include<stdlib.h>

int abs(int a, int b) {
    if (a > b)
        return a - b;
    else
        return b - a;
}

int main() {
    int tracks[] = {55, 58, 60, 70, 18, 90, 150, 160, 184};
    int num_tracks = sizeof(tracks) / sizeof(tracks[0]);

    int current_track, previous_track, total_head_movement = 0;

    printf("Track Sequence: ");


    for (int i = 0; i < num_tracks; i++) {
        printf("%d ", tracks[i]);
    }

    current_track = tracks[0];
    printf("\n\nHead Movement:\n");

    
    for (int i = 1; i < num_tracks; i++) {
        previous_track = current_track;
        current_track = tracks[i];
        int movement = abs(previous_track, current_track);
        total_head_movement += movement;
        printf("Move from %d to %d: %d\n", previous_track, current_track, movement);
    }

    printf("\nTotal Head Movement: %d\n", total_head_movement);
    printf("Average Head Movement: %.2f\n", (float) total_head_movement / num_tracks);

    return 0;
}