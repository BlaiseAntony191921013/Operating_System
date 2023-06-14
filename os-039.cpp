#include <stdio.h>
#include <stdlib.h>

int abs_diff(int a, int b) {
    return abs(a - b);
}

void look(int tracks[], int num_tracks, int start_pos) {
    int i, j, temp, total_movement = 0;
    
    
    for (i = 0; i < num_tracks - 1; i++) {
        for (j = 0; j < num_tracks - i - 1; j++) {
            if (tracks[j] > tracks[j + 1]) {
                temp = tracks[j];
                tracks[j] = tracks[j + 1];
                tracks[j + 1] = temp;
            }
        }
    }
    
 
    int start_index = -1;
    for (i = 0; i < num_tracks; i++) {
        if (tracks[i] >= start_pos) {
            start_index = i;
            break;
        }
    }
    

    printf("Head Movement (Forward):\n");
    for (i = start_index; i < num_tracks; i++) {
        printf("%d ", tracks[i]);
        total_movement += abs_diff(tracks[i], start_pos);
        start_pos = tracks[i];
    }
    

    printf("\nHead Movement (Backward):\n");
    for (i = start_index - 1; i >= 0; i--) {
        printf("%d ", tracks[i]);
        total_movement += abs_diff(tracks[i], start_pos);
        start_pos = tracks[i];
    }
    
    printf("\nTotal Head Movement: %d\n", total_movement);
    printf("Average Head Movement: %.2f\n", (float)total_movement / num_tracks);
}

int main() {
    int tracks[] = {55, 58, 60, 70, 18};
    int num_tracks = sizeof(tracks) / sizeof(tracks[0]);
    int start_pos = 50; 

    printf("Track Positions: ");
    for (int i = 0; i < num_tracks; i++) {
        printf("%d ", tracks[i]);
    }
    printf("\nStarting Position: %d\n", start_pos);
    
    look(tracks, num_tracks, start_pos);

    return 0;
}

