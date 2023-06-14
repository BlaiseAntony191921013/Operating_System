#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 3
#define MAX_FILES 2
#define MAX_FILENAME_LENGTH 20

struct Directory {
    char name[MAX_FILENAME_LENGTH];
    char files[MAX_FILES][MAX_FILENAME_LENGTH];
    int fileCount;
};

struct Directory users[MAX_USERS];

int main() {
    // Create user directories
    for (int i = 0; i < MAX_USERS; i++) {
        printf("Enter name for user directory %d: ", i + 1);
        scanf("%s", users[i].name);
        users[i].fileCount = 0;
    }

    // Create files within user directories
    for (int i = 0; i < MAX_USERS; i++) {
        for (int j = 0; j < MAX_FILES; j++) {
            printf("Enter name for file %d within user directory %s: ", j + 1, users[i].name);
            scanf("%s", users[i].files[j]);
            users[i].fileCount++;
        }
    }

    // Print the directory structure
    printf("\nDirectory Structure:\n");
    for (int i = 0; i < MAX_USERS; i++) {
        printf("\nUser Directory: %s\n", users[i].name);
        printf("Files:\n");
        for (int j = 0; j < users[i].fileCount; j++) {
            printf("- %s\n", users[i].files[j]);
        }
    }

    return 0;
}

