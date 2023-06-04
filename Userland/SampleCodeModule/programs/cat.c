#include <userlandApps.h>

#define SIZE 1024

int cat(char ** args)
{
    char buff[SIZE] = {0};
    char c;
    int i = 0, j =0;
    while((c = getChar()) != EOF)
    {
        if (c == 8)
            { // 8 is ascii's basckspace
                if (i != 0)
                {
                    backspace();
                    i--;
                }
            }
        else if(c == '\n')
        {
            printf(WHITE, "\n");
            while (j != i)
            {
                printChar(buff[j], WHITE);
                j++;
            }
            i = 0;
            j = 0;
            printf(WHITE, "\n");
        } else {
            if(i != SIZE)
            {
                buff[i] = c;
                printChar(buff[i], WHITE);
                i++;
            }
            
        }
    }

    return 0;
}