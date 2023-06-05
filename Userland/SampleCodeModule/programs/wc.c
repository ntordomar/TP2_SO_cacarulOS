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