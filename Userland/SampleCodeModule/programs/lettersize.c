// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <userStdF.h>

int lettersize(char **args)
{
    printf(WHITE, "CHOOSE YOUR FONT SIZE (WE RECOMMEND A NUMBER LOWER OR EQUAL TO 3)\n");
    char buff[50];
    int buffPos = 0;
    char c;

    while (1)
    {

        c = getChar();
        if (c != -1 && c != 0)
        {
            hold(1);
            if (c == '\n')
            {
                newLine();
                buff[buffPos] = 0;
                setCharSize(atoi(buff));
                printf(WHITE, "SIZE WAS CHANGED");
                newLine();
                return 0;
            }
            else
            {
                if (!isDigit(c))
                {
                    printf(WHITE, "DIGITS ONLY :( ABORTING...\n");
                    return 0;
                }
                buff[buffPos++] = c;
                printChar(c, WHITE);
            }
        }
    }
    return 0;
}