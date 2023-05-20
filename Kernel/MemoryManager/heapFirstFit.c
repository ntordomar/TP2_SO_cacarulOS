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
blockLink firstBlock; // The first block of the heap

uint8_t usingHeap = 0;
void initHeap();
void * malloc(size_t wantedBlockSize) {
    _cli();

    if(wantedBlockSize <0) {
        return NULL;
    }

    wantedBlockSize += sizeof(blockLink) + ( 8 - (wantedBlockSize & 7) ); // We align the size of the block to 8 bytes

    if(wantedBlockSize > freeMemory) {
        return NULL;
    }

    if(!usingHeap) {
        initHeap(); //Initializes the heap by inserting a first block that has the size of the entire heap.
    }
    blockMemory previousBlock = &firstBlock;
    blockMemory actualBlock = (&firstBlock)->nextFreeBlock;

    //iterate through the list of free blocks until we find one that is big enough
    while(actualBlock != NULL && actualBlock->blockSize < wantedBlockSize) {
        previousBlock = actualBlock;
        actualBlock = actualBlock->nextFreeBlock;
    }
    
    if(actualBlock == NULL) {
        return NULL; // llegue al final de la lista y no hay bloque con el size suficiente
    }

    // en este punto ya estamos en el bloque que vamos a partir 
    
    void * startPosition = USABLE_MEMORY(actualBlock);

    if(actualBlock->blockSize - wantedBlockSize > MIN_BLOCK_SIZE) {
        // Spliting the block in order to take out the block we will return
        blockMemory remainingBlock  = actualBlock + wantedBlockSize;
        remainingBlock->blockSize = actualBlock->blockSize - wantedBlockSize;
        remainingBlock->nextFreeBlock = actualBlock->nextFreeBlock;
        previousBlock->nextFreeBlock = remainingBlock;
    }else {
        previousBlock->nextFreeBlock = actualBlock->nextFreeBlock;
    }
    freeMemory -= (actualBlock->blockSize + sizeof(blockLink));
    return startPosition;
 
    
    
    
        // primero pregunto si tengo el lugar (sumandole el tamanio del struct + alineacion) 
        // recorre la lista de bloques libres hasta encontrar uno que sea lo suficientemente grande
        // en caso de que lo encuentra:
                // El que vamos a devolver va a ser en el que esta + tamanio del struct
                // en caso de que quede lugar libre, creamos en bloqueEncontrado +  tamanio del bloque + tamanio del struct,un nuevo bloque de tamaño = tamaño bloque - tamaño pedido
                // linkeamos el anterior y el proximo con ese struct
                // retornamos el struct que sacamos :)
    _sti();
    

}

void free(void * ptr) {
    // resto size del struct
    blockLink * blockToInsert = (uint8_t) ptr - sizeof(blockLink);
    blockLink * current = &firstBlock;
    // primero itera hasta encontrar una direccion de memoria donde la proxima se pase 
    for (; current->nextFreeBlock != NULL && current->nextFreeBlock < blockToInsert; current = current->nextFreeBlock) {
        // we are just iterating to get to the right position
    }
    
    if(current + sizeof(blockLink) + current->blockSize == blockToInsert){
        // tenemos que mergear
        current->blockSize += (blockToInsert->blockSize + sizeof(blockLink));
        
    } else {
        // se quedan separados :( Tenemos que insertarlo en la lista.
        blockToInsert->nextFreeBlock = current->nextFreeBlock;
        current->nextFreeBlock = blockToInsert;
        current = blockToInsert;
    }

    // mi direccion de memoria es la misma que la suma entre la pos de memoria de current + current.size
    // IF true, modifico el tamanio al current
    // current + current.size + sizeOF(BLOCK) = current.next
    // ahora preguntamos si coincide el final del bloque con el siguiente bloque
    if(current->nextFreeBlock == NULL) return;
    if(current + sizeof(blockLink) + current->blockSize == current->nextFreeBlock) {
        current->blockSize += sizeof(blockLink) + current->nextFreeBlock->blockSize;
        current->nextFreeBlock = current->nextFreeBlock->nextFreeBlock;
    }
}

void initHeap() {

    size_t alignedAddress;
    alignedAddress = heapMemory;

    if ((alignedAddress & 0x0007) != 0x00) {
        alignedAddress += (8 - 1);
        alignedAddress &= ~(0x0007);

    }


    blockMemory firstUsableBlock = (blockMemory) alignedAddress;
    firstBlock.nextFreeBlock = firstUsableBlock;
    freeMemory -= (sizeof(blockLink) + ( alignedAddress - (size_t) heapMemory));
    firstUsableBlock->blockSize = freeMemory; // We save the usable memory for the user
    usingHeap = 1;
}