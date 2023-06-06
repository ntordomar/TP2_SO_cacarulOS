#include <userlandApps.h>
// #include <userStdF.h>

int loop(char **args)
{
    while (1)
    {
        print("Hello Cacarulo, I am the process ", WHITE);
        printf(WHITE, "%d\n", getCurrentPid());
        hold(60);
    }
}