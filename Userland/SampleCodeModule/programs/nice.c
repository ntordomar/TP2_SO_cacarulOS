// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <userlandApps.h>

int nice(char ** args){
    int pid = atoi(args[0]);
    int niceness = atoi(args[1]);
    setNiceness(pid, niceness);
    return 0;
}