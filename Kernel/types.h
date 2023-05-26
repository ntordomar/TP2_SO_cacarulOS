#define READY 0
#define BLOCKED 1
#define RUNNING 2

#include <stdint.h>

typedef struct memoryBlock {
    uint8_t * base;
    size_t size;
    uint8_t * current;
} memoryBlock;

typedef struct processType {
    int pid;
    char * name;
    int parent;
    memoryBlock * heap;
    memoryBlock * stack;
    int status;
} processType;

typedef struct PCB {
    size_t priority;
    processType * process;
} PCB;

typedef struct schNode {
    PCB * processControlBlock;
    struct schList * next;
} schNode;

typedef schNode * schList;
