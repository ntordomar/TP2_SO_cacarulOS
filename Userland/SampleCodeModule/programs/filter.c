#include <userlandApps.h>

#define SIZE 1024
char checkIfVowel(char c);
int filter(char ** args)
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
                if(checkIfVowel(buff[j]))
                {
                    printChar(buff[j], WHITE);
                }
                
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

char checkIfVowel(char c){
    int i = 0;
    char vowels [] = {'A','E','I','O','U',0};
    while(vowels[i] != 0)
    {
        if(vowels[i++] == c)
        {
            return 1;
        }
    }
    return 0;    
}