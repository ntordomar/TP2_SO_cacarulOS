#include <userlandApps.h>

int mem(char **args)
{
    memoryInfo *currentMemory = getMemoryInfo();
    printf(GREEN, "\nCurrent Memory Status:\n");
    printf(WHITE, "Total Memory: %d\n", currentMemory->total);
    printf(WHITE, "Used Memory: %d\n", currentMemory->used);
    printf(WHITE, "Free Memory: %d\n", currentMemory->free);
    return 0;
}