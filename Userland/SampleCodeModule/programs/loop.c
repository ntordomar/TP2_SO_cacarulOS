// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <userlandApps.h>

int loop(char **args)
{
    while (1)
    {
        print("HELLO CACARULO, I AM THE PROCESS ", WHITE);
        printf(WHITE, "%d", getCurrentPid());
        printChar('\n',WHITE);
        hold(60);
    }
}