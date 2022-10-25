/* sampleCodeModule.c */
// terminal
#include <user_syscalls.h>
#include <userStdF.h>
#include <userLib.h>
#include <stdint.h>
#include<tron.h>
void help();
void lettersize();
void clear();
void backspace();
void newLine();
void time();
void tron();
char * v = (char*)0xB8000 + 79 * 2;

static int yPos = 0;
static int xPos = 0;
static int initialCharSize = 1;

static char* commandList[] = {"HELP", "TRON", "LETTERSIZE","CLEAR", "TIME"};
static void (*commandFunctions[5])(void) = {help, tron, lettersize,clear, time};

static int commandCount = 5;

static char lineBuffer[256]; //ir completando a medida que sigamos en la misma 
static lineCantChar = 0;

int isDigit(char c){
    return c >= '0' && c<= '9';
}

void analizeCommand(){ // int strcmp 0 si si 1 sino
    for (int i =0; i<commandCount; i++){
        if (strcmp(lineBuffer, commandList[i]) == 0){
            (*commandFunctions[i])();
            lineCantChar = 0;
            return;
        } 
    }
    print(xPos, yPos, "COMMAND NOT FOUND", WHITE);
    newLine();
    lineCantChar = 0;
    
}

void time(){
    print(xPos, yPos, "TIEMPO ACTUAL:", WHITE);
    newLine();
    printCurrentTime(xPos, yPos);
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
    print(xPos,yPos,"BIENVENIDOS A LA TERMINAL.", WHITE);
    newLine();
    print(xPos, yPos, "Los comandos disponibles son:", WHITE);
    newLine();
    print(xPos, yPos, "HELP, TRON, LETTERSIZE, CLEAR, TIME", WHITE);
    newLine();
    print(xPos, yPos, "LETTERSIZE: ", WHITE);

}

void tron(){
    tronGame();
    sys_clear_screen();
    xPos = 0;
    yPos = 0;
}

void backspace(){
    if(xPos <= 0) {
    if(yPos == 0) return;

        xPos = 1024;
        yPos -= 16 * initialCharSize;
    } else {
        xPos -= initialCharSize*8;
    }
    sys_write_char(xPos,yPos,' ',WHITE);
}    


void lettersize() {
     sys_write(xPos, yPos, "Ingrese un numerito", 19, WHITE);
     xPos+=initialCharSize*8;
    newLine();
    char buff[50];
    int buffPos = 0;
    char c;

    while(1){
         
        c = getc();  
        if (c!=-1 && c!=0){
    for(int i = 0; i<9000; i++);

            if(c == '\n'){
                newLine();
                buff[buffPos] = 0;
                sys_change_font_size(myAtoi(buff));
                initialCharSize = myAtoi(buff);
                sys_write(xPos,yPos,"SE HA CAMBIADO EL NUMERITO",26,WHITE);
                xPos += initialCharSize*8;
                newLine();
                return;
            }else{
                if(!isDigit(c)){
                    print(xPos,yPos,"lo ingresado no es un numero taradooo!", WHITE);
                    newLine();
                    return;
                }
                buff[buffPos++] = c;
                sys_write_char(xPos, yPos, c, WHITE);
                xPos+=initialCharSize*8;

            }
        }
    }
}
void clear(){
    sys_clear_screen();
    xPos = 0;
    yPos = 0;
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
            if(c == 8){ // 8 es el ascii del basckspace
                if(lineCantChar != 0){ 
                    backspace();
                    lineCantChar--;
                }
            } else if(c == '\n'){
                newLine();
                lineBuffer[lineCantChar] = 0;
                analizeCommand();
                
            }
            else{
                lineBuffer[lineCantChar++] = c;
             
               sys_write_char(xPos, yPos, c, WHITE);
               xPos +=initialCharSize*8;
            }
        
        }
    }
    
}



