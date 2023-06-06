// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <userlandApps.h>

int mem(char **args)
{
    memoryInfo *memInfo = getMemoryInfo();
    printf(WHITE, "Total memory: %d\n", memInfo->total);
    printf(WHITE, "Used memory: %d\n", memInfo->used);
    printf(WHITE, "Free memory: %d\n", memInfo->free);
    return 0;
}
