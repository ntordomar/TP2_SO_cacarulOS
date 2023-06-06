// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "./include/sync.h"
#include <locale.h>
#include <lib.h>

mutexType mutexArray[SEM_MAX]; // we only use one mutex per semaphore

void mutexInit()
{
    for(int i = 0; i<SEM_MAX; i++)
    {
        mutexArray[i].blockedProcesses = NULL;
    }
}

void mutexLock(mutex_t mutexID)
{
    if(!enterCriticalRegion(&mutexArray[mutexID].value)){
        mutexArray[mutexID].currentOwnerPID = getCurrentPid();
    }
    else{
       enqueue(mutexArray[mutexID].blockedProcesses, getCurrentPCB());
       blockProcess(getCurrentPid());
       mutexArray[mutexID].currentOwnerPID = getCurrentPid();
    }
}
void mutexUnlock(mutex_t mutexID)
{
    mutexArray[mutexID].currentOwnerPID = -1;
    PCB * headOfQueue = dequeue(mutexArray[mutexID].blockedProcesses);
    if(headOfQueue != NULL){
        unblockProcess(headOfQueue->process->pid);
    }else{
        mutexArray[mutexID].value = 0;
    }
}

void mutexCreate(mutex_t mutexID)
{
    if (mutexID >= SEM_MAX || mutexID < 0)
    {
        return;
    }
    if(mutexArray[mutexID].blockedProcesses == NULL)
    mutexArray[mutexID].blockedProcesses = createQueue();
    mutexArray[mutexID].value = 0;
    mutexArray[mutexID].currentOwnerPID = -1;
}

void mutexDelete(mutex_t mutexID)
{
    if (mutexID > SEM_MAX || mutexID < 0)
    {
        return;
    }
    destroyQueue(mutexArray[mutexID].blockedProcesses);
}
