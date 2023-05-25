#include "process.h"



int createProcess(char * name, int parent, size_t heapSize, size_t stackSize, char ** args, void* code){
    if(code == NULL || name == NULL){
        return -1;
    }

    


    processType * process = malloc(sizeof(processType));
    if(process == NULL){
        return -1; // No hay memoria para crear un nuevo proceso
    }

    process->pid = getNewPid(); // funcion implementada en el sheduler
    
    process->name = malloc(strlen(name)+1);
    if(process->name == NULL){
        return -1;
    }
    strcpy(process->name, name);
    
    process->parent = getCurrentPid(); // esta funcion va a estar implementada en el scheduler

    process->heap = malloc(sizeof(memoryBlock));
    if(process->heap == NULL){
        return -1;
    }
    process->heap->base = malloc(heapSize * STACK_SIZE); // preguntar que onda la stack size??????? en ambos casos seria 4096
    if(process->heap->base == NULL){
        return -1;
    }
    process->heap->size = heapSize * STACK_SIZE;
    process->heap->current = process->heap->base;

    process->stack = malloc(sizeof(memoryBlock));
    if(process->stack == NULL){
        return -1;
    }
    process->stack->base = malloc(stackSize * STACK_SIZE);
    if(process->stack->base == NULL){
        return -1;
    }
    process->stack->size = stackSize * STACK_SIZE;
    process->stack->current = process->stack->base + process->stack->size;
    process->status = READY;

    // A PARTIR DE ESTE PUNTO YA PUSIMOS TODA LA INFORMACION ADENTRO DEL PROCESO.
    // LO AGREGO A MI LISTA DE PROCESOS. ANALIZAR TODOS JUNTOS, TIPO PARA QUE QUEREMOS ESO SI YA LO TENEMOS EN EL SCHEDULER
    // ahora deberia agregarlo a la lista en el scheduler, y tmb deberia crear toda la estructura del stack
    

    return process->pid;
}