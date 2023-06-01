#include "./include/process.h"
#include <video.h>
#include "../include/heap.h"
#include "../include/lib.h"
#include "../include/scheduler.h"
int biggerPidAvailable = 1;

int createProcess(char *name, int parent, size_t heapSize, size_t stackSize, char **args, void *code)
{
    if (code == NULL || name == NULL)
    {
        return -1;
    }

    processType *process = (processType *)malloc(sizeof(processType));
    if (process == NULL)
    {
        return -1; // No hay memoria para crear un nuevo proceso
    }

    process->pid = getNewPid(); // funcion implementada en el sheduler

    process->name = malloc(strlen(name) + 1);
    if (process->name == NULL)
    {
        return -1;
    }
    strcpy(process->name, name);
    if (parent == -1)
    {
        process->parent = getCurrentPid(); // getCurrentPid(); // esta funcion va a estar implementada en el scheduler
    }
    else
    {
        process->parent = parent;
    }

    process->heap = (uint64_t *)malloc(sizeof(memoryBlock));
    if (process->heap == NULL)
    {
        return -1;
    }
    process->heap->base = (uint64_t *)malloc(heapSize); // preguntar que onda la stack size??????? en ambos casos seria 4096
    if (process->heap->base == NULL)
    {
        return -1;
    }
    process->heap->size = heapSize;
    process->heap->current = (uint64_t *)process->heap->base;

    process->stack = (uint64_t *)malloc(sizeof(memoryBlock));
    if (process->stack == NULL)
    {
        return -1;
    }
    process->stack->base = (uint64_t *)malloc(stackSize);
    if (process->stack->base == NULL)
    {
        return -1;
    }
    process->stack->size = stackSize;
    process->stack->current = process->stack->base + process->stack->size;
    process->status = READY;

    // A PARTIR DE ESTE PUNTO YA PUSIMOS TODA LA INFORMACION ADENTRO DEL PROCESO.
    // LO AGREGO A MI LISTA DE PROCESOS. ANALIZAR TODOS JUNTOS, TIPO PARA QUE QUEREMOS ESO SI YA LO TENEMOS EN EL SCHEDULER
    // ahora deberia agregarlo a la lista en el scheduler, y tmb deberia crear toda la estructura del stack
    // createProcessStack(code, args, (uint64_t *)process->stack->base + process->stack->size);
    process->stack->current = createStack((char *)process->stack->base + process->stack->size, code, args, &processWrapper);
    addProcess(process);
    return process->pid;
}

int getNewPid()
{
    return biggerPidAvailable++;
}

int killProcess(int pid)
{

    PCB *processPCB = findPcbEntry(pid);

    if (processPCB == NULL || processPCB->process == NULL)
    {
        return -1;
    }

    if (findPcbEntry(processPCB->process->parent) == NULL)
    {
        processPCB->process->status = DEAD;
    }
    else
    {
        processPCB->process->status = ZOMBIE;
    }

    if (pid == getCurrentPid())
    {
        forceScheduler();
    }
    return 0;
}


int blockProcess(int pid){

    PCB *processPCB = findPcbEntry(pid);

    if (processPCB == NULL || processPCB->process == NULL)
    {
        return -1;
    }

    processPCB->process->status = BLOCKED;

    if (pid == getCurrentPid())
    {
        forceScheduler();
    }
    
    return 0;
}

int unblockProcess(int pid){
    PCB *processPCB = findPcbEntry(pid);

    if (processPCB == NULL || processPCB->process == NULL)
    {
        return -1;
    }

    processPCB->process->status = READY;
    return 0;
}

void processWrapper(int code(char **args), char **args)
{
    int ret = code(args);
    draw_char(300, 300, 'A', GREEN, BLACK);
    killProcess(getCurrentPid());
    draw_char(300, 350, 'B', GREEN, BLACK);
}
