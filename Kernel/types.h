#define READY 0
#define BLOCKED 1
#define RUNNING 2
#define ZOMBIE 3
#define DEAD 4

#define FD_READ 0
#define FD_WRITE 1
#define FD_ERROR 2
#define SHELL 0 // FD of shell process

#include <stdint.h>
#include <stddef.h>

typedef struct memoryBlock
{
    uint64_t *base;
    size_t size;
    uint64_t *current;
} memoryBlock;

typedef struct processType
{
    int pid;
    char *name;
    int parent;
    memoryBlock *heap;
    memoryBlock *stack;
    int status;
    int return_value;
    int fd[3];
} processType;

typedef struct PCB
{
    size_t priority;
    size_t ticks;
    processType *process;
} PCB;

typedef struct schNode
{
    PCB *processControlBlock;
    struct schList *next;
} schNode;

typedef schNode *schList;

typedef struct
{
    int name;
    int readSemId;
    int writeSemId;
    unsigned int writePos;
    unsigned int readPos;
    char *pipeBuffer;
    uint8_t eof;
    int leftToRead;
} pipeType;
