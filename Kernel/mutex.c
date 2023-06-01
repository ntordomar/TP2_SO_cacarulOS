#include "./include/sync.h"

mutexType mutexArray[SEM_MAX]; // we only use one mutex per semaphore

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
    if (mutexID > SEM_MAX || mutexID < 0)
    {
        return;
    }
        
    mutexArray[mutexID].blockedProcesses = createQueue();
    mutexArray[mutexID].value = 1;
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