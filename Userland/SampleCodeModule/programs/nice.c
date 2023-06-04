#include <userlandApps.h>

int nice(char ** args){
    int pid = atoi(args[0]);
    int nice = atoi(args[1]);
    setNiceness(pid, nice);
    printf(BLUE, "VOLVI6\n");
    return 0;
}