#include <stdio.h>
#include <stdint.h>
#define STACK_SIZE 4096
#define READY 0
#define BLOCKED 1
#define RUNNING 2
typedef struct memoryBlock {
    uint8_t * base;
    size_t size;
    void * current;
} memoryBlock;

typedef struct processType {
    int pid;
    char * name;
    int parent;
    memoryBlock * heap;
    memoryBlock * stack;
    int status;
} processType;



int createProcess(char * name, int parent, size_t heapSize, size_t stackSize, char ** args, void * code);