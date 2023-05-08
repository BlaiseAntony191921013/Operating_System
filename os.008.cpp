#include <stdio.h>
#include <stdlib.h>

int main() {
    int num_tracks = 5;
    int track_position[] = {55, 58, 60, 70, 18};
    int current_position = 50;
    int total_head_movement = 0;

    
    for (int i = 0; i < num_tracks; i++) {
        total_head_movement += abs(current_position - track_position[i]);
        current_position = track_position[i];
    }

    printf("Average head movement: %f\n", (float)total_head_movement/num_tracks);

    return 0;
}