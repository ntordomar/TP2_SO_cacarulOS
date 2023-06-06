#include <stddef.h>
#include <stdint.h>
#include <queueADT.h>

#define IDLE_PRIORITY 0
#define MAX_PRIORITY 5
#define MIN_PRIORITY 1
#define QUANTUM 2 // 5 ticks del timer es 1 quantum

uint8_t schedulerIsEnabled();
void initScheduler();
void includeTerminal(int pid);
void addProcess(processType *process);
void stopProcess(uint64_t *stackPointer, uint64_t *stackSegment);
PCB *findNextAvailableProcess();
uint64_t *switchProcess(uint64_t *stackPointer, uint64_t *stackSegment);
PCB *findPcbEntry(int pid);
int getCurrentPid();
int changePriority(int pid, int newPriority);
int hasMoreTicks();
PCB *getIdleProcessPCB();
PCB *getCurrentPCB();
Queue ** getQueues();
void removeProcess(PCB *pcb);
void yield();

PCB * getForegroundProcess();