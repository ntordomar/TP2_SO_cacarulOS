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
    currentP->status = RUNNING;
    enabled = 1;
}

void addProcess(processType * process) {
    //insert schNodes into the list with a priority of zero
    PCB * pcb = (PCB *)malloc(sizeof(PCB));
    pcb->priority = 0;
    pcb->process = process;
    schNode * node = (schNode *) malloc(sizeof(schNode));
    node->processControlBlock = pcb;
    processes->next = node;
    cantProcess++;
}

uint8_t * switchProcess(uint8_t * stackPointer){
    currentP->stack->current = stackPointer; // guardo el stack pointer del proceso actual
    draw_string(100,300,"init scheduler", 0x0F, GREEN, BLACK);
    schNode * iter = processes;
    while (iter != NULL && ( iter->processControlBlock == NULL|| iter->processControlBlock->process->status != READY) ){ // busca el prox proceso ready
        iter = iter->next;
    }

    if (iter == NULL){ // no hay procesos ready, devolvemos el mismo que antes!!!!!!!!!!!!!!
        draw_string(100,100,"no hay procesos ready", 0x0F, GREEN, BLACK);
        return stackPointer;
    }
            draw_string(600,100," hay procesos ready", 0x0F, GREEN, BLACK);

    currentP->status = READY; // el proceso actual pasa a estar ready
    currentP = iter->processControlBlock->process; // el proceso actual es el que encontre.
    currentP->status = RUNNING; // el proceso actual pasa a estar running
    // draw_string(100,100,"switching process", 0x0F, GREEN, BLACK);
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
    
