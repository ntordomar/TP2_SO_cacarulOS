#define READY 0
#define BLOCKED 1
#define RUNNING 2
#define ZOMBIE 3
#define DEAD 4

#include <stdint.h>
#include <stddef.h>

typedef struct memoryBlock {
    uint64_t * base;
    size_t size;
    uint64_t * current;
} memoryBlock;

typedef struct processType {
    int pid;
    char * name;
    int parent;
    memoryBlock * heap;
    memoryBlock * stack;
    int status;
    int return_value;
} processType;

typedef struct PCB {
    size_t priority;
    size_t ticks;
    processType * process;
} PCB;

typedef struct schNode {
    PCB * processControlBlock;
    struct schList * next;
} schNode;

typedef schNode * schList;