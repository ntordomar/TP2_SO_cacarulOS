// This is the implementation of the heap that uses the first fit algorithm with a linked list
// of free blocks. The free blocks are sorted by address, and adyacent free blocks are merged

#include "heap.h"
#include "../include/interrupts.h"
#include <stddef.h>
#include <stdint.h>

typedef struct blockLink // This is the structure of a free block
{
    struct blockLink * nextFreeBlock; /*<< The next free block in the list. */
    size_t blockSize;                     /*<< The size of the free block. */
} blockLink;

typedef struct blockLink * blockMemory;

#define USABLE_MEMORY(x) (x + sizeof(blockLink))  
#define MIN_BLOCK_SIZE (sizeof(blockLink) * 2) // The minimum size of a block is twice the size of the blockLink struct

size_t freeMemory = TOTALHEAPSIZE; // The amount of free memory in the heap
uint8_t heapMemory[TOTALHEAPSIZE]; 
blockLink * firstBlock; // The first block of the heap

uint8_t usingHeap = 0;

void * malloc(size_t wantedBlockSize) {
    
    if(wantedBlockSize <0 || wantedBlockSize > freeMemory) {
        return NULL;
    }

    if(!usingHeap) {
        initHeap(); //Initializes the heap by inserting a first block that has the size of the entire heap.
    }
    blockMemory previousBlock = firstBlock;
    blockMemory actualBlock = firstBlock->nextFreeBlock;

    //iterate through the list of free blocks until we find one that is big enough
    while(actualBlock != NULL && actualBlock->blockSize < wantedBlockSize) {
        previousBlock = actualBlock;
        actualBlock = actualBlock->nextFreeBlock;
    }
    
    if(actualBlock == NULL) {
        return NULL;
    }

    // en este punto ya estamos en el bloque que vamos a partir / null
    
    void * startPosition = USABLE_MEMORY(actualBlock);

    if(actualBlock->blockSize - wantedBlockSize > MIN_BLOCK_SIZE) {
        // Spliting the block in order to take out the block we will return
        int returnedBlockSize = wantedBlockSize + sizeof(blockLink);
        blockMemory remainingBlock  = actualBlock + returnedBlockSize;
        remainingBlock->blockSize = actualBlock->blockSize - returnedBlockSize;
        remainingBlock->nextFreeBlock = actualBlock->nextFreeBlock;
        previousBlock->nextFreeBlock = remainingBlock;
    }else {
        previousBlock->nextFreeBlock = actualBlock->nextFreeBlock;
    }
    freeMemory -= (actualBlock->blockSize + sizeof(blockLink));
    return startPosition;
 
    
    
    _cli();
        // primero pregunto si tengo el lugar (sumandole el tamanio del struct + alineacion) 
        // recorre la lista de bloques libres hasta encontrar uno que sea lo suficientemente grande
        // en caso de que lo encuentra:
                // El que vamos a devolver va a ser en el que esta + tamanio del struct
                // en caso de que quede lugar libre, creamos en bloqueEncontrado +  tamanio del bloque + tamanio del struct,un nuevo bloque de tamaño = tamaño bloque - tamaño pedido
                // linkeamos el anterior y el proximo con ese struct
                // retornamos el struct que sacamos :)
    _sti();
    

}

void initHeap() {
    blockMemory firstUsableBlock = (blockMemory) heapMemory;
    firstBlock->nextFreeBlock = firstUsableBlock;
    firstUsableBlock->blockSize = TOTALHEAPSIZE - sizeof(blockLink); // We save the usable memory for the user
    freeMemory -= sizeof(blockLink);
    usingHeap = 1;
}