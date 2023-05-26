#include "./include/heap.h"
#include "./include/interrupts.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

typedef struct blockLink // This is the structure of a free block
{
    struct blockLink * nextFreeBlock; /*<< The next free block in the list. */
    size_t blockSize;                     /*<< The size of the free block. */
} blockLink;

//Keeping a list of free blocks and a list of allocated blocks
blockLink headBlock; // The first block of the free heap

uint64_t heapMemory[TOTALHEAPSIZE];

size_t freeMemory = 0; // The amount of free memory in the heap

uint8_t usingHeap = 0;


void * malloc(size_t wantedBlockSize) {

    if (!usingHeap){
        initHeap();
    }

    if (wantedBlockSize > freeMemory){
        return NULL;
    }

    blockLink * currentBlock = headBlock.nextFreeBlock;
    blockLink * previousBlock = &headBlock;

    while(currentBlock != NULL && currentBlock->blockSize<wantedBlockSize){
        previousBlock = currentBlock;
        currentBlock = currentBlock->nextFreeBlock;
    }

    //We didnt find any block big enough
    if (currentBlock == NULL){
        return NULL;
    }

    void * pointerToReturn;

    //We found a block big enough
    if (currentBlock->blockSize - wantedBlockSize > 2 * sizeof(blockLink)){ // Hay que dividir
        blockLink * newBlock = (blockLink * )((uint64_t * )currentBlock + sizeof(blockLink) + wantedBlockSize);
        newBlock->blockSize = currentBlock->blockSize - wantedBlockSize - sizeof(blockLink);
        newBlock->nextFreeBlock = currentBlock->nextFreeBlock;

        //Preparo el bloque que voy a devolver
        currentBlock->blockSize = wantedBlockSize;
        currentBlock->nextFreeBlock = NULL;

        freeMemory -= wantedBlockSize + sizeof(blockLink);
        pointerToReturn = (uint64_t *) currentBlock + sizeof(blockLink);
        previousBlock->nextFreeBlock = newBlock;

    } else {
        pointerToReturn = (uint64_t *)currentBlock + sizeof(blockLink);
        freeMemory -= currentBlock->blockSize;
        previousBlock->nextFreeBlock = currentBlock->nextFreeBlock;
    }

    return pointerToReturn;

}

void free(void * ptr){


    blockLink * blockToFree = (blockLink *)((uint64_t *)ptr - sizeof(blockLink));

    
    blockLink * prev = &headBlock;
    blockLink * curr = headBlock.nextFreeBlock;

    while (curr != NULL && (uint64_t *)curr < (uint64_t*)blockToFree){
        prev = curr;
        curr = curr->nextFreeBlock;
    }

    //Si el bloque que quiero liberar es el ultimo
    if (curr == NULL){
        prev->nextFreeBlock = blockToFree;
        blockToFree->nextFreeBlock = NULL;
    } else {
        blockToFree->nextFreeBlock = curr;
        prev->nextFreeBlock = blockToFree;
    }


    //Mergeamos a izquierda
    if  ((uint64_t * )prev + sizeof(blockLink) + prev->blockSize == (uint64_t *)blockToFree){
        prev->blockSize += blockToFree->blockSize + sizeof(blockLink);
        prev->nextFreeBlock = blockToFree->nextFreeBlock;
        freeMemory += sizeof(blockLink);
        blockToFree = prev;
    }

    //Mergeamos a derecha
    if ((uint64_t * )blockToFree + sizeof(blockLink) + blockToFree->blockSize == (uint64_t *)blockToFree->nextFreeBlock){
        blockToFree->blockSize += blockToFree->nextFreeBlock->blockSize + sizeof(blockLink);
        blockToFree->nextFreeBlock = blockToFree->nextFreeBlock->nextFreeBlock;
        freeMemory += sizeof(blockLink);
    }

    freeMemory += blockToFree->blockSize;
}

void initHeap(){
    headBlock.nextFreeBlock = (blockLink *) heapMemory;
    headBlock.blockSize = TOTALHEAPSIZE;
    blockLink* firstBlock = headBlock.nextFreeBlock;
    firstBlock->blockSize = TOTALHEAPSIZE - sizeof(blockLink);
    freeMemory = firstBlock->blockSize;
    firstBlock->nextFreeBlock = NULL;
    usingHeap = 1;
}