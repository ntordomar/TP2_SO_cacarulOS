// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <video.h>
#include "../include/lib.h"
#include <sync.h>

void freeProcess(PCB *processPCB);
int biggerPidAvailable = 1;

int createProcess(char *name, int parent, size_t heapSize, size_t stackSize, char **args, void *code, char foreground, int *fds)
{
    if (code == NULL || name == NULL)
    {
        return -1;
    }

    processType *process = (processType *)malloc(sizeof(processType));
    if (process == NULL)
    {
        return -1; // There is no memory to create a new process
    }

    process->pid = getNewPid();

    process->name = malloc(strlen(name) + 1);
    if (process->name == NULL)
    {
        free(process);
        return -1;
    }
    strcpy(process->name, name);
    if (parent == -1)
    {
        process->parent = getCurrentPid();
    }
    else
    {
        process->parent = parent;
    }

    process->heap = (memoryBlock *)malloc(sizeof(memoryBlock));
    if (process->heap == NULL)
    {
        free(process->name);
        free(process);
        return -1;
    }
    process->heap->base = (uint64_t *)malloc(heapSize);
    if (process->heap->base == NULL)
    {
        free(process->heap);
        free(process->name);
        free(process);
        return -1;
    }
    process->heap->size = heapSize;
    process->heap->current = (uint64_t *)process->heap->base;

    process->stack = (memoryBlock *)malloc(sizeof(memoryBlock));
    if (process->stack == NULL)
    {
        free(process->heap->base);
        free(process->heap);
        free(process->name);
        free(process);
        return -1;
    }
    process->stack->base = (uint64_t *)malloc(stackSize);
    if (process->stack->base == NULL)
    {
        free(process->stack);
        free(process->heap->base);
        free(process->heap);
        free(process->name);
        free(process);
        return -1;
    }
    process->stack->size = stackSize;
    process->stack->current = process->stack->base + process->stack->size;
    process->status = READY;

    // Setting IN OUT and ERROR file descriptors to the shell as default.
    process->fd[FD_READ] = fds[0];
    process->fd[FD_WRITE] = fds[1];
    process->fd[FD_ERROR] = SHELL;

    process->foreground = foreground;

    process->stack->current = createStack((uint64_t *)process->stack->base + process->stack->size, code, args, &processWrapper);
    process->semId = semCreateAnonymous(0);
    process->cant = 0;
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

    // if it is already a zombie or dead, do nothing

    if (findPcbEntry(processPCB->process->parent) == NULL || processPCB->process->status == ZOMBIE)
    {
        processPCB->process->status = DEAD;
        removeProcess(processPCB);
        for(int i = 0; i<processPCB->process->cant; i++)
        {
            free(processPCB->process->myMemory[i]);
        }
        freeProcess(processPCB);
    }
    else
    {
        processPCB->process->status = ZOMBIE;
        semPost(processPCB->process->semId);
        semClose(processPCB->process->semId);
    }

    if (pid == getCurrentPid())
    {

        forceScheduler();
    }
    return 0;
}

int killCurrentForeground(int semId)
{
    PCB *currentPCB = findPcbEntry(getForegroundProcess());
    if (currentPCB == NULL)
        return -1;

    // kill process that is running in foreground if it is not the shell
    if (!killChildren(currentPCB->process->pid))
    {
        if (currentPCB->process->status == BLOCKED)
            semSet(semId, 1);
        return killProcess(currentPCB->process->pid);
    }
    return 0;
}

int killChildren(int ppid)
{
    int count = 0;
    Queue **myQueues = getQueues();
    for (int i = MIN_PRIORITY; i <= MAX_PRIORITY; i++)
    {
        int *killedProcesses = dequeueAllChildren(myQueues[i], ppid);
        for (int j = 0; killedProcesses[j] != -1; j++)
        {
            killProcess(killedProcesses[j]);
            count++;
        }
        free(killedProcesses);
    }
    return count;
}

int blockProcess(int pid)
{

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

int unblockProcess(int pid)
{
    PCB *processPCB = findPcbEntry(pid);

    if (processPCB == NULL || processPCB->process == NULL)
    {
        return -1;
    }

    processPCB->process->status = READY;
    if (getCurrentPCB()->priority == -1)
    {
        forceScheduler();
    }
    return 0;
}

void processWrapper(int code(char **args), char **args)
{
    openAnonymous(getCurrentPCB()->process->semId);
    code(args);
    int pid = getCurrentPid();
    killProcess(pid);
}

void setFileDescriptor(int pid, int index, int value)
{
    findPcbEntry(pid)->process->fd[index] = value;
}

processInfo *getProcessInfo(int pid)
{
    PCB *processPCB = findPcbEntry(pid);
    processInfo *info = (processInfo *)malloc(sizeof(processInfo));
    if (info == NULL)
    {
        return NULL;
    }
    info->pid = pid;
    info->parent = processPCB->process->parent;
    info->state = processPCB->process->status;
    info->priority = processPCB->priority;
    info->foreground = processPCB->process->foreground;
    info->name = malloc(strlen(processPCB->process->name) + 1);
    if (info->name == NULL)
    {
        free(info);
        return NULL;
    }
    info->name = strcpy(info->name, processPCB->process->name);
    info->rsp = processPCB->process->stack->current;
    info->rbp = processPCB->process->stack->base;
    return info;
}

int waitpid(int pid)
{
    PCB *processToWait = findPcbEntry(pid);

    if (processToWait == NULL)
    {
        return -1;
    }
    int pidRetValue = processToWait->process->pid;
    semWait(processToWait->process->semId);

    killProcess(processToWait->process->pid);
    return pidRetValue;
}

void freeProcess(PCB *processPCB)
{
    free(processPCB->process->stack->base);
    free(processPCB->process->heap->base);
    free(processPCB->process->heap);
    free(processPCB->process->stack);
    free(processPCB->process->name);
    semDestroy(processPCB->process->semId);
    free(processPCB->process);
    free(processPCB);
}

void toggleBlock(int pid)
{
    PCB *processPCB = findPcbEntry(pid);
    if (processPCB == NULL)
    {
        return;
    }
    if (processPCB->process->status == BLOCKED)
    {
        unblockProcess(pid);
    }
    else if (processPCB->process->status == READY)
    {
        blockProcess(pid);
    }
}
