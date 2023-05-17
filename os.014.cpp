#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 3
#define MAX_REFERENCES 20

int getPageFaults(int pageFrames[], int referenceSequence[], int numFrames, int numReferences) {
    int pageFaults = 0;

    
    for (int i = 0; i < numFrames; i++) {
        pageFrames[i] = -1;  
    }

    
    for (int i = 0; i < numReferences; i++) {
        int page = referenceSequence[i];
        bool pageFound = false;

        
        for (int j = 0; j < numFrames; j++) {
            if (pageFrames[j] == page) {
                pageFound = true;
                break;
            }
        }

        
        if (!pageFound) {
            pageFaults++;
            int replaceIndex = -1;
            int farthestIndex = i + 1;

        
            for (int j = 0; j < numFrames; j++) {
                int framePage = pageFrames[j];
                bool pageFutureFound = false;

                
                for (int k = i + 1; k < numReferences; k++) {
                    if (referenceSequence[k] == framePage) {
                        pageFutureFound = true;
                        if (k > farthestIndex) {
                            farthestIndex = k;
                            replaceIndex = j;
                        }
                        break;
                    }
                }

                
                if (!pageFutureFound) {
                    replaceIndex = j;
                    break;
                }
            }

            
            pageFrames[replaceIndex] = page;
        }
    }

    return pageFaults;
}

int main() {
    int pageFrames[MAX_FRAMES];
    int referenceSequence[MAX_REFERENCES] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int numFrames = 3;
    int numReferences = 20;

    int pageFaults = getPageFaults(pageFrames, referenceSequence, numFrames, numReferences);
    printf("Number of Page Faults: %d\n", pageFaults);

    return 0;
}