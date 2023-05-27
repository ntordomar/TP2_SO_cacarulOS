#include "./include/scheduler.h"
#include <video.h>

processType * currentP;

schList processes = NULL;
size_t cantProcess = 0;

uint8_t enabled = 0;

// processType idleProcess;

uint8_t schedulerIsEnabled() {
    return enabled;
}

void initScheduler(int pid){
    
    // idleProcess = *process;
    processes = malloc(sizeof(schNode));
    processes->processControlBlock = NULL;
    processes->next = NULL;
}
void includeTerminal(int pid){
    
    currentP = findProcessByPid(pid);
    currentP->status = RUNNING; // CAMBIOS
    enabled = 1;
    forceChangeOfProcess(currentP->stack->current); // CAMBIOS
}

void addProcess(processType * process) {
    //insert schNodes into the list with a priority of zero
    PCB * pcb = (PCB *)malloc(sizeof(PCB));
    pcb->priority = 0;
    pcb->process = process;
    schNode * node = (schNode *) malloc(sizeof(schNode));
    node->processControlBlock = pcb;
    schNode * iter = processes;
    while(iter->next != NULL){ // CAMBIOS
        iter = iter->next;
    }
    iter->next = node;
    cantProcess++;
}

uint64_t * switchProcess(uint64_t * stackPointer, uint64_t * stackSegment){
    currentP->stack->current = stackPointer; // guardo el stack pointer del proceso actual // CAMBIOS
    currentP->stack->base = stackSegment;
    schNode * iter = processes;
    while (iter != NULL && ( iter->processControlBlock == NULL|| iter->processControlBlock->process->status != READY) ){ // busca el prox proceso ready
        iter = iter->next;
    }

    if (iter == NULL){ // no hay procesos ready, devolvemos el mismo que antes!!!!!!!!!!!!!!
        return stackPointer;
    }
    currentP->status = READY; // el proceso actual pasa a estar ready
    currentP = iter->processControlBlock->process; // el proceso actual es el que encontre.
    currentP->status = RUNNING; // el proceso actual pasa a estar running
    return currentP->stack->current;
}

processType * findProcessByPid(int pid){
    schNode * iter = processes;
    while (iter != NULL && iter->processControlBlock->process->pid != pid){
        iter = iter->next;
    }
    if (iter == NULL){
        return NULL;
    }
    return iter->processControlBlock->process;
}
    
