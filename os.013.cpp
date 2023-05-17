#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100
#define MAX_FILENAME_LENGTH 50

struct File {
    char name[MAX_FILENAME_LENGTH];
};

struct Directory {
    char name[MAX_FILENAME_LENGTH];
    struct File files[MAX_FILES];
    int fileCount;
};

int main() {
    struct Directory directory;
    strcpy(directory.name, "CSE");
    directory.fileCount = 0;


    strcpy(directory.files[directory.fileCount].name, "A");
    directory.fileCount++;
    strcpy(directory.files[directory.fileCount].name, "B");
    directory.fileCount++;
    strcpy(directory.files[directory.fileCount].name, "C");
    directory.fileCount++;

    printf("Directory: %s\n", directory.name);
    printf("Files:\n");
    for (int i = 0; i < directory.fileCount; i++) {
        printf("- %s\n", directory.files[i].name);
    }

    return 0;
}