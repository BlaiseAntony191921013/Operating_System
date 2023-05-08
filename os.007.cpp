#include <stdio.h>

int main() {
    int page_frames = 3;
    int page_reference[] = {1,2,3,2,1,5,2,1,6,2,5,6,3,1,3,6,1,2,4,3};
    int page_table[page_frames];
    int page_faults = 0;
    int i, j, k, lru_index;

    for (i = 0; i < page_frames; i++) {
        page_table[i] = -1; 
    }

    for (i = 0; i < sizeof(page_reference)/sizeof(page_reference[0]); i++) {
        int page = page_reference[i];
        int page_found = 0;

        
        for (j = 0; j < page_frames; j++) {
            if (page_table[j] == page) {
                page_found = 1;
                break;
            }
        }

        
        if (!page_found) {
            page_faults++;

            
            lru_index = 0;
            for (j = 1; j < page_frames; j++) {
                if (page_table[j] < page_table[lru_index]) {
                    lru_index = j;
                }
            }

        
            page_table[lru_index] = page;
        }

        
        printf("Page Table: ");
        for (k = 0; k < page_frames; k++) {
            if (page_table[k] == -1) {
                printf("[ ] ");
            } else {
                printf("[%d] ", page_table[k]);
            }
        }
        printf("\n");
    }

    printf("Number of page faults: %d\n", page_faults);

    return 0;
}