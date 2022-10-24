/* sampleCodeModule.c */
// terminal
#include <user_syscalls.h>
#include <userStdF.h>
#include <userLib.h>
#include <stdint.h>
void tron();
void help();
void newLine();
void lettersize();

char * v = (char*)0xB8000 + 79 * 2;

static int yPos = 0;
static int xPos = 0;
static int initialCharSize = 1;

static char* commandList[] = {"HELP", "TRON", "LETTERSIZE"};
static void (*commandFunctions[5])(void) = {help, tron, lettersize};

static int commandCount = 2;

static char lineBuffer[256]; //ir completando a medida que sigamos en la misma 
static lineCantChar = 0;

void analizeCommand(){ // int strcmp 0 si si 1 sino
    for (int i =0; i<commandCount; i++){
        if (strcmp(lineBuffer, commandList[i]) == 0){
            (*commandFunctions[i])();
            lineCantChar = 0;
            return;
        } 
    }
    sys_write(xPos, yPos, "command not found", 17, 1);
    lineCantChar = 0;
    newLine();
}

int myAtoi(char* str)
{
    int res = 0;
    for (int i = 0; str[i] != '\0'; ++i)
        res = res * 10 + str[i] - '0';

    return res;
}

void help(){
    sys_write(xPos, yPos, "Ingrese un numerito", 19, 1);
    newLine();
    
    char buff[50] = {0};
    int buffPos = 0;
    char c;

    while(1){
        c = getc();   
        for(int i = 0; i< 9000; i++){;}

        if (c!=-1 && c!=0){

            if(c = '\n'){
                sys_change_font_size(myAtoi(buff));
                return;
            }else{
                buff[buffPos++] = c;
                sys_write_char(xPos, yPos, c, 1);
            }
        }
    }
    // sys_write_char(xPos, yPos, c, 1);
    // sys_change_font_size(myAtoi(c));
}

void tron(){
    ;
}

void lettersize() {
    ;
}

void newLine(){
    xPos = 0;
    yPos = yPos + initialCharSize * 16;
}



int main() {
 
    while(1){
        char c  = getc();
        for(int i = 0; i< 9000; i++){;}

        if (xPos == 1024){
            newLine();
        }

        if (c != -1 && c!= 0){
            if(c == 8){
                if(lineCantChar != 0){ 
                    //backSpace();
                    lineCantChar--;
                }
            } else if(c == '\n'){
                newLine();
                lineBuffer[lineCantChar] = 0;
                analizeCommand();
                
            }
            else{
                lineBuffer[lineCantChar++] = c;
             
               sys_write_char(xPos+=initialCharSize*8, yPos, c, 1);
            }
        
        }
    }
    
}



