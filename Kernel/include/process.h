#include <stdio.h>
#include <stdint.h>
#include "heap.h"
#include "lib.h"
#include "scheduler.h"

#define STACKPOS(pos) (uint64_t * ) (stackStart -(pos))
#define SS 2 * 8
#define RSP 3 * 8
#define RFLAGS 4 * 8
#define CS 5 * 8
#define RIP 6 * 8
#define GPR_START 6 * 8
#define RDI 12 * 8
#define CANT_REGISTER 15

int createProcess(char * name, int parent, size_t heapSize, size_t stackSize, char ** args, void * code);
int getNewPid();
int killProcess(int pid);
void processWrapper(int code(char **args), char ** arg);