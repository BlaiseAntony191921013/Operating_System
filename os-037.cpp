#include <stdio.h>
#include <stdbool.h>

int search(int pages[], int num_pages, int value, int start_index) {
    for (int i = start_index; i < num_pages; i++) {
        if (pages[i] == value)
            return i;
    }
    return -1;
}

int optimal(int pages[], int num_pages, int num_frames) {
    int frames[num_frames];
    bool is_available[num_frames];
    int page_faults = 0;

    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
        is_available[i] = false;
    }

    for (int i = 0; i < num_pages; i++) {
        int page = pages[i];
        bool is_present = false;

  
        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == page) {
                is_present = true;
                break;
            }
        }

  \
        if (!is_present) {
            int farthest = i;
            int index = -1;

            for (int j = 0; j < num_frames; j++) {
                int page_index = search(pages, num_pages, frames[j], i + 1);
                if (page_index == -1) {
                    index = j;
                    break;
                }

                if (page_index > farthest) {
                    farthest = page_index;
                    index = j;
                }
            }

            frames[index] = page;
            is_available[index] = true;
            page_faults++;
        }
    }

    return page_faults;
}

int main() {
    int num_frames = 3;
    int pages[] = {4, 1, 2, 4, 3, 2, 1, 5};
    int num_pages = sizeof(pages) / sizeof(pages[0]);

    int page_faults = optimal(pages, num_pages, num_frames);

    printf("Number of Page Faults: %d\n", page_faults);

    return 0;
}

