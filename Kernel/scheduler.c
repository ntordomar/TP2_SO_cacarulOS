#include "./include/scheduler.h"
int priorityQuantum[6] = {-1, 16, 8, 4, 2, 1};


PCB * currentPCB;

schList processes = NULL;
size_t cantProcess = 0;
uint8_t enabled = 0;

Queue* queues[6]; // priority queues

// processType idleProcess;

uint8_t schedulerIsEnabled() {
    return enabled;
}

void initScheduler() {
    for(int i = MIN_PRIORITY; i <= MAX_PRIORITY; i++) {
        queues[i] = createQueue();
    }
}

void includeTerminal(int pid){
    currentPCB = findPcbEntry(pid);
    currentPCB->process->status = RUNNING; 
    enabled = 1;
    forceChangeOfProcess(currentPCB->process->stack->current);
}

void addProcess(processType * process) {
    //insert schNodes into the list with a priority of zero
    PCB * pcb = (PCB *)malloc(sizeof(PCB));
    pcb->priority = MAX_PRIORITY;
    pcb->process = process;
    pcb->ticks = 0;//QUANTUM*priorityQuantum[pcb->priority];
    schNode * node = (schNode *) malloc(sizeof(schNode));
    node->processControlBlock = pcb;

    //Adding process to the max priority queue.
    enqueue(queues[node->processControlBlock->priority], node->processControlBlock);
    cantProcess++;
}

void stopProcess(uint64_t * stackPointer, uint64_t * stackSegment) {
    currentPCB->process->stack->current = stackPointer; // guardo el stack pointer del proceso actual // CAMBIOS
    currentPCB->process->stack->base = stackSegment;
    if(currentPCB->ticks == priorityQuantum[currentPCB->priority]*QUANTUM) {
        // the process used all its quantum
        if(currentPCB->priority > MIN_PRIORITY) {
            dequeueByData(queues[currentPCB->priority], currentPCB->process->pid);
            currentPCB->priority--;
            enqueue(queues[currentPCB->priority], currentPCB); // le bajo la prioridad
            
        }else {
            dequeueByData(queues[currentPCB->priority], currentPCB->process->pid);
            enqueue(queues[currentPCB->priority], currentPCB); 
        }
    }
}

PCB* findNextAvailableProcess() {
    PCB * elementToReturn;
    for(int i = MAX_PRIORITY; i >= MIN_PRIORITY; i--) {
        if ((elementToReturn = findElement(queues[i])) != NULL){
            return elementToReturn;
        }
    }
    if(currentPCB->process->status == RUNNING) {
        return currentPCB;
    } else {  
        return NULL;
    }
}

uint64_t * switchProcess(uint64_t * stackPointer, uint64_t * stackSegment) {
    stopProcess(stackPointer, stackSegment);
    schNode * nextAvailableProcess;
    nextAvailableProcess = findNextAvailableProcess();
    if (currentPCB->process->status == RUNNING) {
        currentPCB->process->status = READY; // el proceso actual pasa a estar ready
        currentPCB->ticks = 0;    
    } else if (currentPCB->process->status == DEAD) {
        dequeueByData(queues[currentPCB->priority],currentPCB->process->pid);
        // freeProcess(currentPCB->process);
        free(currentPCB);
    }

    
    currentPCB = nextAvailableProcess; // el proceso actual es el que encontre.
    currentPCB->process->status = RUNNING; // el proceso actual pasa a estar running
    return  currentPCB->process->stack->current;
}


PCB * findPcbEntry(int pid) {
    PCB * elementToReturn;
    for(int i = MAX_PRIORITY; i >= MIN_PRIORITY; i--) {
        elementToReturn = findElementByPid(queues[i], pid);        
        if (elementToReturn != NULL) {
            return elementToReturn;
        }
    }
    return NULL;
}

int getCurrentPid() {
    return currentPCB->process->pid;
}

void changePriority(int pid, int newPriority) {
    PCB * processToChange =  findPcbEntry(pid);
    // if(processToChange->process->status == BLOCKED) return;
    
    dequeueByData(queues[processToChange->priority], pid);
    if(newPriority > MAX_PRIORITY) {
        processToChange->priority = MAX_PRIORITY;
    } else if(newPriority < MIN_PRIORITY) {
        processToChange->priority = MIN_PRIORITY;
    } else {
        processToChange->priority = newPriority;
    }
    enqueue(queues[processToChange->priority], processToChange);
}

int hasMoreTicks() {
    if(currentPCB->process->status != RUNNING) return 0;
    if(currentPCB->ticks >= priorityQuantum[currentPCB->priority] * QUANTUM) {
        return 0;
    } else {
        currentPCB->ticks++;
        return 1;
    }
}       

void removeProcess(PCB * pcb) {
    dequeueByData(queues[pcb->priority], pcb->process->pid);
    cantProcess--;
}