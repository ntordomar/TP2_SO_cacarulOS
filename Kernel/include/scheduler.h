#include <stddef.h>
#include <stdint.h>
#include "heap.h"
#include <queueADT.h>

#define MAX_PRIORITY 5
#define MIN_PRIORITY 1
#define QUANTUM 5 // 5 ticks del timer es 1 quantum



uint8_t schedulerIsEnabled();
void initScheduler();
void includeTerminal(int pid);
void addProcess(processType * process);
void stopProcess(uint64_t * stackPointer, uint64_t * stackSegment);
PCB* findNextAvailableProcess();
uint64_t * switchProcess(uint64_t * stackPointer, uint64_t * stackSegment);
processType * getCurrentProcess();
PCB * findPcbEntry(int pid);
int getCurrentPid();
void changePriority(int pid, int newPriority);
int hasMoreTicks();
PCB* getIdleProcessPCB();