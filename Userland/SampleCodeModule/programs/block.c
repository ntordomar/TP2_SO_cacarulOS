#include <userlandApps.h>

int block (char ** args) {
    int pid = atoi(args[0]);
    setBlock(pid);
    return 0;
}