
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