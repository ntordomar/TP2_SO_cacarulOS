#include "./include/sync.h"
#include <lib.h>
#include <heap.h>
#include <video.h>

semaphoreType *semaphores;

void semInit()
{
    semaphores = (semaphoreType *) malloc(sizeof(semaphoreType) * SEM_MAX);
    int i;
    // Initialize all semaphores to NULL
    for (i = 0; i < SEM_MAX; i++)
    {
        cleanSemaphore(i);
        mutexCreate(i);
    }
}

sem_t semCreate(char *name, int initValue)
{
    int i = 0;
    // Find first free position in the array
    while (i < SEM_MAX && semaphores[i].name != NULL)
    {
        i++;
    }
    if (i == SEM_MAX)
    {
        // No free positions
        return -1;
    }
    // Create semaphore
    semaphores[i].name = malloc(strlen(name) + 1); // +1 for '\0' character
    strcpy(semaphores[i].name, name);
    semaphores[i].value = initValue;
    semaphores[i].blockedProcesses = createQueue();
    return i;
}

sem_t semOpen(char *nameSem) {
    int i = 0;
    // Find semaphore with given name
    while (i < SEM_MAX && (semaphores[i].name == NULL || strcmp(semaphores[i].name, nameSem) != 0))
    {
        i++;
    }
    if (i == SEM_MAX)
    {
        // No semaphore with given name
        return -1;
    }
    if(semaphores[i].destroying)
    {
        return -1;
    }
    
    semaphores[i].activeProcesses[getCurrentPid()] = 1;
    semaphores[i].activeProcessCant++;
    return i;
}

int semClose(sem_t semId){
    if (semId > SEM_MAX || semId<0 || semaphores[semId].name == NULL || semaphores[semId].activeProcesses[getCurrentPid()] == 0 )
    {
        return -1;
    }

    

    semaphores[semId].activeProcesses[getCurrentPid()] = 0;
    semaphores[semId].activeProcessCant--;

    if(semaphores[semId].activeProcessCant == 0)
    {
        if(semaphores[semId].destroying)
        {
            unblockProcess(semaphores[semId].destroyerPID);
        }
    }
    return 1;
}   

int semDestroy(sem_t semId){

    if ( semaphores[semId].name == NULL || semaphores[semId].destroying)
    {
        return -1;
    }

    semaphores[semId].destroyerPID = getCurrentPid();
    semaphores[semId].destroying = 1;


    if(semaphores[semId].activeProcessCant != 0){
        blockProcess(getCurrentPid());
    }
    
    // already unblocked
    free(semaphores[semId].name);
    destroyQueue(semaphores[semId].blockedProcesses);
    cleanSemaphore(semId);
    return 0;
}


void cleanSemaphore(int semId){
    semaphores[semId].name = NULL;
    for(int j = 0; j<MAX_CANT_PROCESSES; j++){
        semaphores[semId].activeProcesses[j] = 0;
    }
    semaphores[semId].destroyerPID = -1;
    semaphores[semId].destroying = 0;
    semaphores[semId].activeProcessCant = 0;
}

int semWait(sem_t semId)
{
    if (semId < 0 || semId > SEM_MAX){
        return -1;
    }
    
    mutexLock(semId);
    if(semaphores[semId].value != 0) 
    {
        semaphores[semId].value--;
        mutexUnlock(semId);

    } else {
        enqueue(semaphores[semId].blockedProcesses, getCurrentPCB());
        mutexUnlock(semId);
        blockProcess(getCurrentPid());
    }  
    
}

int semPost(sem_t semId)
{
    if (semId < 0 || semId > SEM_MAX){
        return -1;
    }
    
    mutexLock(semId);
    int semValue = semaphores[semId].value;
    if(isEmpty(semaphores[semId].blockedProcesses)){
        semaphores[semId].value++;
    }
    mutexUnlock(semId);
    if(semValue == 0)
    {
        PCB* unblockedProcess = dequeue(semaphores[semId].blockedProcesses);

        if(unblockedProcess != NULL)
        {
            unblockProcess(unblockedProcess->process->pid);
        }
        
    }
    
}