#include <stdio.h>
#include <heap.h>

#define MAX_CANT_PROCESSES 100

#define CANT_REGISTER 15

int createProcess(char * name, int parent, size_t heapSize, size_t stackSize, char ** args, void * code, char foreground, int * fds);
int getNewPid();
int killProcess(int pid);
void processWrapper(int code(char **args), char ** arg);
int blockProcess(int pid);
int unblockProcess(int pid);
void setFileDescriptor(int pid, int index, int value);
processInfo * getProcessInfo(int pid);
int waitpid(int pid);
int killCurrentForeground(int semId);
int killChildren(int ppid);
void toggleBlock(int pid);