#include "./include/process.h"

int biggerPidAvailable = 1;

int createProcess(char * name, int parent, size_t heapSize, size_t stackSize, char ** args, void* code){
    if(code == NULL || name == NULL){
        return -1;
    }

    processType * process = (processType *)malloc(sizeof(processType));
    if(process == NULL){
        return -1; // No hay memoria para crear un nuevo proceso
    }

    process->pid = getNewPid(); // funcion implementada en el sheduler
    
    process->name = malloc(strlen(name)+1);
    if(process->name == NULL){
        return -1;
    }
    strcpy(process->name, name);
    
    process->parent = 0; //getCurrentPid(); // esta funcion va a estar implementada en el scheduler

    process->heap = malloc(sizeof(memoryBlock));
    if(process->heap == NULL){
        return -1;
    }
    process->heap->base = malloc(heapSize); // preguntar que onda la stack size??????? en ambos casos seria 4096
    if(process->heap->base == NULL){
        return -1;
    }
    process->heap->size = heapSize;
    process->heap->current = process->heap->base;

    process->stack = malloc(sizeof(memoryBlock));
    if(process->stack == NULL){
        return -1;
    }
    process->stack->base = malloc(stackSize);
    if(process->stack->base == NULL){
        return -1;
    }
    process->stack->size = stackSize;
    process->stack->current = process->stack->base + process->stack->size;
    process->status = READY;

    // A PARTIR DE ESTE PUNTO YA PUSIMOS TODA LA INFORMACION ADENTRO DEL PROCESO.
    // LO AGREGO A MI LISTA DE PROCESOS. ANALIZAR TODOS JUNTOS, TIPO PARA QUE QUEREMOS ESO SI YA LO TENEMOS EN EL SCHEDULER
    // ahora deberia agregarlo a la lista en el scheduler, y tmb deberia crear toda la estructura del stack
    createProcessStack(code, args, process->stack->base + process->stack->size);    
    addProcess(process);
    return process->pid;
}

int createProcessStack(uint8_t * code, char** args, uint8_t * stackStart){
    
    for (int i = 0; i<CANT_REGISTER ; i++){
        *(STACKPOS(GPR_START + i)) = i;
    }

    // pisamos el valor de RDI, puesto que ahi va a estar el puntero a los argumentos
    *(STACKPOS(RDI)) = (uint8_t *) args;

    *(STACKPOS(RIP)) = (uint8_t *) code;
    *(STACKPOS(CS)) = 0x8;
    *(STACKPOS(RFLAGS)) = 0x202;
    *(STACKPOS(RSP)) = stackStart - 8; // mirar grafico para mejor entendimiento
    *(STACKPOS(SS)) = 0x0;


    // el stack start va a ser donde empieza el stack, la posicion mas alta de memoria, dsps va a bajar.
    // abajo de todo 
    /*
                     0000000000
                     12ava -> RDI          (stackStart - 1*12)           
                     . . .
                     . . .
                     . . .
                     SEGUNDO BLOQUE (2)
            RSP ->   PRIMER BLOQUE (stackStart - 1 * 8)
      stackStart ->  FFFFFFFFFF
    */
}

int getNewPid(){
    return biggerPidAvailable++;

}