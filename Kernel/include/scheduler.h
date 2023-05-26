#include <stddef.h>
#include "../types.h"
#include <stdint.h>
#include "heap.h"

void initScheduler(int pid);
void addProcess(processType * process);
uint8_t * switchProcess(uint8_t * stackPointer);
processType * getCurrentProcess();
processType * findProcessByPid(int pid);
uint8_t schedulerIsEnabled();
void includeTerminal(int pid);