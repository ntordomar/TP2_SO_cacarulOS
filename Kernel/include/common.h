#include <stdint.h>
#include <stddef.h>

typedef struct {
    char * name;
    int pid;
    int parent;
    uint64_t rsp;
    uint64_t rbp;
    size_t priority;
    char foreground;
    int state;
} processInfo;

typedef struct 
{
    int total;
    int used;
    int free;
} memoryInfo;

typedef struct
{
    char * name;
    int semValue;
    char tryingToDestroy;
    int activeProcessCant;
    
} semInfo;
