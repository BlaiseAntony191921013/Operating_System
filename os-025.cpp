#include <stdio.h>

int main()
{
    int blockSize = 1;   // size of each block in bytes
    int totalBlocks = 100;   // total number of blocks in the file
    int blockToAdd = 50;   // block number to add
    int blockSizeInBytes = blockSize * sizeof(int);   // size of each block in bytes
    int blockAddress, prevBlockAddress, nextBlockAddress, i;

    // Contiguous Allocation
    int startingBlock = 0;   // starting block of the file
    int endingBlock = totalBlocks - 1;   // ending block of the file
    int totalIOContiguous = 0;   // total number of disk I/O operations for contiguous allocation
    if (blockToAdd == startingBlock) {   // block added at the beginning
        blockAddress = startingBlock * blockSizeInBytes;   // block address in bytes
        for (i = endingBlock; i >= blockToAdd; i--) {
            totalIOContiguous += 2;   // read old block, write new block
        }
    }
    else if (blockToAdd == endingBlock) {   // block added at the end
        blockAddress = blockToAdd * blockSizeInBytes;   // block address in bytes
        for (i = startingBlock; i <= blockToAdd - 1; i++) {
            totalIOContiguous += 2;   // read old block, write new block
        }
    }
    else {   // block added in the middle
        blockAddress = blockToAdd * blockSizeInBytes;   // block address in bytes
        for (i = startingBlock; i <= endingBlock; i++) {
            totalIOContiguous++;   // read each block
        }
        totalIOContiguous++;   // read index block
        totalIOContiguous++;   // write new block
    }
    printf("Contiguous Allocation - Total Disk I/O operations: %d\n", totalIOContiguous);

    // Linked Allocation
    int FAT[totalBlocks];   // file allocation table
    for (i = 0; i < totalBlocks; i++) {
        FAT[i] = i + 1;   // initialize FAT to point to the next block
    }
    FAT[totalBlocks - 1] = -1;   // last block points to -1
    int startingBlockLinked = 0;   // starting block of the file
    int endingBlockLinked = totalBlocks - 1;   // ending block of the file
    int totalIOLinked = 0;   // total number of disk I/O operations for linked allocation
    if (blockToAdd == startingBlockLinked) {   // block added at the beginning
        blockAddress = startingBlockLinked * blockSizeInBytes;   // block address in bytes
        totalIOLinked++;   // read first FAT block
        nextBlockAddress = FAT[blockToAdd] * blockSizeInBytes;   // address of next block
        totalIOLinked++;   // read next block
        FAT[blockToAdd] = blockToAdd;   // update FAT
        totalIOLinked++;   // write new FAT block
        totalIOLinked++;   // write new block
    }

