#include <stddef.h>
#include "../types.h"
#include <stdint.h>
#include "heap.h"

void initScheduler(int pid);
void addProcess(processType * process);
uint64_t * switchProcess(uint64_t * stackPointer, uint64_t * stackSegment);
processType * getCurrentProcess();
processType * findProcessByPid(int pid);
uint8_t schedulerIsEnabled();
void includeTerminal(int pid);