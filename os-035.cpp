#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define TOTAL_BLOCKS 16
#define RESERVED_BLOCKS 8
#define AVAILABLE_BLOCKS (TOTAL_BLOCKS - RESERVED_BLOCKS)
#define BLOCK_SIZE 1024
#define MIN_FILE_SIZE 1024

typedef struct {
    bool is_allocated;
    int next_block;
} Block;

void initialize_blocks(Block blocks[]) {
    for (int i = 0; i < TOTAL_BLOCKS; i++) {
        blocks[i].is_allocated = false;
        blocks[i].next_block = -1;
    }
}

int allocate_blocks(Block blocks[], int num_blocks) {
    int start_block = -1;
    int current_block = -1;
    int allocated_blocks = 0;

    for (int i = RESERVED_BLOCKS; i < TOTAL_BLOCKS; i++) {
        if (!blocks[i].is_allocated) {
            if (start_block == -1) {
                start_block = i;
                current_block = i;
            } else {
                blocks[current_block].next_block = i;
                current_block = i;
            }
            blocks[i].is_allocated = true;
            allocated_blocks++;

            if (allocated_blocks == num_blocks) {
                blocks[current_block].next_block = -1;
                return start_block;
            }
        }
    }

    return -1;
}

void display_blocks(Block blocks[]) {
    printf("Block\tStatus\t\tNext Block\n");
    for (int i = 0; i < TOTAL_BLOCKS; i++) {
        printf("%d\t%s\t\t", i, blocks[i].is_allocated ? "Allocated" : "Free");
        if (blocks[i].next_block != -1) {
            printf("%d\n", blocks[i].next_block);
        } else {
            printf("N/A\n");
        }
    }
}

int main() {
    Block blocks[TOTAL_BLOCKS];
    initialize_blocks(blocks);

    printf("File System Blocks:\n");
    display_blocks(blocks);

    int file_size;
    printf("\nEnter the size of the file in KB: ");
    scanf("%d", &file_size);

    if (file_size < MIN_FILE_SIZE) {
        printf("File size must be at least 1 KB.\n");
        return 0;
    }

    int num_blocks = file_size / BLOCK_SIZE;
    if (file_size % BLOCK_SIZE != 0) {
        num_blocks++;
    }

    if (num_blocks > AVAILABLE_BLOCKS) {
        printf("Not enough contiguous blocks available for the file.\n");
        exit(0);
    }

    int start_block = allocate_blocks(blocks, num_blocks);

    if (start_block == -1) {
        printf("Error allocating blocks to the file.\n");
        return 0;
    }

    printf("\nFile allocated successfully!\n");
    printf("Start Block: %d\n", start_block);
    printf("Number of Blocks: %d\n", num_blocks);

    printf("\nUpdated File System Blocks:\n");
    display_blocks(blocks);

    return 0;
}

