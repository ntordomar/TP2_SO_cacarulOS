#include <stdio.h>
#include <stdint.h>
#include "heap.h"
#include "lib.h"
#include "scheduler.h"

#define STACKPOS(pos) (uint8_t * ) (stackStart -(pos))
#define SS 1 * 8
#define RSP 2 * 8
#define RFLAGS 3 * 8
#define CS 4 * 8
#define RIP 5 * 8
#define GPR_START 6 * 8
#define RDI 11 * 8
#define CANT_REGISTER 15

int createProcess(char * name, int parent, size_t heapSize, size_t stackSize, char ** args, void * code);
int createProcessStack(uint8_t * code, char** args, uint8_t * stackStart);
int getNewPid();