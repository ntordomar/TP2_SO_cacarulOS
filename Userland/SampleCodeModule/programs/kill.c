#include <userlandApps.h>

int kill(char **args)
{
    int pid = atoi(args[0]);
    if (pid > 0)
    {
        if (killProcess(pid) == 0)
        {
            printf(BLUE, "Process %d deleted\n", pid);
        }
        else
        {
            printf(RED, "The process %d does not exist\n", pid);
        }
    }

    return 0;
}