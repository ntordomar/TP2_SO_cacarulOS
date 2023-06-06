// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "./include/scheduler.h"
#include "heap.h"
#include <keyBoardHandler.h>
#include <lib.h>
int priorityQuantum[6] = {1, 16, 8, 4, 2, 1};

PCB *currentPCB;
int foregroundProcess;

size_t cantProcess = 0;
uint8_t enabled = 0;

Queue *queues[6]; // priority queues

uint8_t schedulerIsEnabled()
{
    return enabled;
}

void initScheduler()
{
    for (int i = MIN_PRIORITY; i <= MAX_PRIORITY; i++)
    {
        queues[i] = createQueue();
    }
}

void includeTerminal(int pid)
{
    currentPCB = findPcbEntry(pid);
    currentPCB->process->status = RUNNING;
    keyboardHandlerInit();
    enabled = 1;
    forceChangeOfProcess(currentPCB->process->stack->current);
}

void addProcess(processType *process)
{
    // insert schNodes into the list with a priority of zero
    PCB *pcb = (PCB *)malloc(sizeof(PCB));
    if (pcb == NULL)
    {
        return;
    }
    pcb->priority = MAX_PRIORITY;
    pcb->process = process;
    pcb->ticks = 0;

    // Set the current foreground process
    if (pcb->process->pid != 1 && pcb->process->pid != 2 && pcb->process->foreground == 1)
    {
        foregroundProcess = pcb->process->pid;
    }

    // Adding process to the max priority queue.
    enqueue(queues[pcb->priority], pcb);
    cantProcess++;
}

void stopProcess(uint64_t *stackPointer, uint64_t *stackSegment)
{
    currentPCB->process->stack->current = stackPointer;
    if (currentPCB->priority == IDLE_PRIORITY)
    {
        return;
    }
    if (currentPCB->ticks == priorityQuantum[currentPCB->priority] * QUANTUM) // process runed the whole quantum
    {
        // the process used all its quantum
        if (currentPCB->priority > MIN_PRIORITY)
        {
            changePriority(currentPCB->process->pid, currentPCB->priority - 1); // decrease its priority
        }
        else
        {

            dequeueByData(queues[currentPCB->priority], currentPCB->process->pid);
            enqueue(queues[currentPCB->priority], currentPCB);
        }
    }
    else // process didnt run the whole quantum
    {
        if (currentPCB->priority < MAX_PRIORITY)
        {
            int newPriority = currentPCB->priority + (int)(1 / (double)(currentPCB->ticks / priorityQuantum[currentPCB->priority] * QUANTUM));
            changePriority(currentPCB->process->pid, newPriority);
        }
        else
        {
            dequeueByData(queues[currentPCB->priority], currentPCB->process->pid);
            enqueue(queues[currentPCB->priority], currentPCB);
        }
    }
}

PCB *findNextAvailableProcess()
{
    PCB *elementToReturn;
    for (int i = MAX_PRIORITY; i >= MIN_PRIORITY; i--)
    {
        if ((elementToReturn = findElement(queues[i])) != NULL)
        {
            return elementToReturn;
        }
    }
    if (currentPCB->process->status == RUNNING)
    {
        return currentPCB;
    }
    else
    {
        return getIdleProcessPCB();
    }
}

uint64_t *switchProcess(uint64_t *stackPointer, uint64_t *stackSegment)
{

    stopProcess(stackPointer, stackSegment);
    PCB *nextAvailableProcess;
    nextAvailableProcess = findNextAvailableProcess();
    if (currentPCB->process->status == RUNNING)
    {
        currentPCB->process->status = READY; // the process is now ready
        currentPCB->ticks = 0;
    }
    currentPCB = nextAvailableProcess;     // the actual process is the one i found
    currentPCB->process->status = RUNNING; // the process is now running
    return currentPCB->process->stack->current;
}

PCB *findPcbEntry(int pid)
{
    PCB *elementToReturn;
    for (int i = MAX_PRIORITY; i >= MIN_PRIORITY; i--)
    {
        elementToReturn = findElementByPid(queues[i], pid);
        if (elementToReturn != NULL)
        {
            return elementToReturn;
        }
    }
    return NULL;
}

int getCurrentPid()
{
    return currentPCB->process->pid;
}

PCB *getCurrentPCB()
{
    return currentPCB;
}

int changePriority(int pid, int newPriority)
{
    PCB *processToChange = findPcbEntry(pid);

    if (processToChange == NULL)
    {
        return -1;
    }
    dequeueByData(queues[processToChange->priority], pid);
    if (newPriority > MAX_PRIORITY)
    {
        processToChange->priority = MAX_PRIORITY;
    }
    else if (newPriority < MIN_PRIORITY - 1) //-1 because of IDLE process priority
    {
        processToChange->priority = MIN_PRIORITY;
    }
    else
    {
        processToChange->priority = newPriority;
    }
    enqueue(queues[processToChange->priority], processToChange);
    return 0;
}

int hasMoreTicks()
{
    if (currentPCB->process->status != RUNNING)
    {
        return 0;
    }
    if (currentPCB->ticks >= priorityQuantum[currentPCB->priority] * QUANTUM)
    {
        return 0;
    }
    else
    {
        currentPCB->ticks++;
        return 1;
    }
}

void removeProcess(PCB *pcb)
{
    dequeueByData(queues[pcb->priority], pcb->process->pid);
    cantProcess--;
}

PCB *getIdleProcessPCB()
{
    return peek(queues[0]); // list with only the idle process
}

int *getPidsArray()
{
    int *pids = (int *)malloc(sizeof(int) * cantProcess);
    if (pids == NULL)
    {
        return NULL;
    }
    int i = MIN_PRIORITY;
    int cantPids = 0;
    for (; i <= MAX_PRIORITY; i++)
    {
        cantPids += retPids(queues[i], pids + cantPids);
    }
    pids[cantProcess - 1] = -1;
    return pids;
}

Queue **getQueues()
{
    return queues;
}

int getForegroundProcess()
{
    return foregroundProcess;
}

void yield()
{
    currentPCB->ticks = priorityQuantum[currentPCB->priority] * QUANTUM;
    forceScheduler();
}
