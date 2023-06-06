// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <userlandApps.h>
int wc(char **args)
{
    int c, counter = 1;
    while ((c = getChar()) != EOF)
    {
        if (c == '\n')
        {
            newLine();
            counter++;
        }
        else
        {
            printChar(c, WHITE);
        }
    }
    printf(WHITE, "\nTotal lines: %d\n", counter);
    return 0;
}