#include <userStdF.h>

void lettersize() {
    print("Write a number", WHITE);
    // sys_write(xPos, yPos, "Ingrese un numerito", 19, WHITE);
    // xPos+=initialCharSize*8;
    newLine();
    char buff[50];
    int buffPos = 0;
    char c;

    while(1){
         
        c = getChar();  
        if (c!=-1 && c!=0){
    //for(int i = 0; i<9000; i++);
            hold(1);
            if(c == '\n'){
                newLine();
                buff[buffPos] = 0;
                setCharSize(atoi(buff));
                print("SIZE WAS CHANGED", WHITE);
                //xPos += initialCharSize*8;
                newLine();
                return;
            } else {
                if(!isDigit(c)){
                    print("lo ingresado no es un numero taradooo!", WHITE);
                    newLine();
                    return;
                }
                buff[buffPos++] = c;
                // sys_write_char(xPos, yPos, c, WHITE);
                // xPos+=initialCharSize*8;
                printChar(c, WHITE);

            }
        }
    }
}