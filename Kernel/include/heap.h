
#ifndef HEAP_H
#define HEAP_H
#include <common.h>

#define TOTALHEAPSIZE ((size_t)(52 * 4096 * 2))

void *malloc(size_t size);
void free(void *ptr);
void initHeap();
memoryInfo *getHeapInfo();

#endif