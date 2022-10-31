#include <userStdF.h>

void lettersize() {
    printf(WHITE,"CHOOSE YOUR FONT SIZE (WE RECOMMEND A NUMBER LOWER OR EQUAL TO 3)\n");
    char buff[50];
    int buffPos = 0;
    char c;

    while(1){
         
        c = getChar();  
        if (c!=-1 && c!=0){
            hold(1);
            if(c == '\n'){
                newLine();
                buff[buffPos] = 0;
                setCharSize(atoi(buff));
                printf(WHITE,"SIZE WAS CHANGED");
                newLine();
                return;
            } else {
                if(!isDigit(c)){
                    printf(WHITE,"DIGITS ONLY :( ABORTING...\n");
                    return;
                }
                buff[buffPos++] = c;
                printChar(c, WHITE);

            }
        }
    }
}