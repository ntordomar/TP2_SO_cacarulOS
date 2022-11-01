/* sampleCodeModule.c */
// terminal
#include <userStdF.h>
#include <userLib.h>
#include <stdint.h>
#include<tron.h>
#include <piano.h>
#include <inforeg.h>
#include <time.h>
#include <memory.h>
#include <lettersize.h>
#include <exceptions.h>
void help();
void clear();
void backspace();
void newLine();
void tron();
void piano();
char * v = (char*)0xB8000 + 79 * 2; // sirve?


static char* commandList[] = {"HELP", "TRON", "LETTERSIZE","CLEAR", "TIME", "INFOREG", "MEMORY", "DIVIDEBYZERO", "OPCODE", "PIANO"};
static void (*commandFunctions[])(char * param) = {help, tron, lettersize, clear, time, inforeg, memory,divideByZero, opCode, piano};

static int commandCount = 10;

static char lineBuffer[256] = {0}; 
static int lineCantChar = 0;



void analizeCommand(){
    
    char argument[50];
    divideString(lineBuffer,argument,' ');
    for (int i =0; i<commandCount; i++){
        if (strcmp(lineBuffer, commandList[i]) == 0){
            (*commandFunctions[i])(argument);
            lineCantChar = 0;
        
            return;
        } 
    }
    
    printf(WHITE, "%s COMMAND NOT FOUND\n", lineBuffer);
    lineCantChar = 0;
    
}





void help(){
    printf(GREEN,"Welcome to cacaHELP The following available commands are:\n\n\n");
    printf(GREEN,  "COMMAND name:   USE:\n");
    printf(WHITE,"HELP:       SHOWS YOU THE AVAILABLE COMMANDS, AND THEIR USAGE\n");
    printf(WHITE, "TRON:       PLAY TRON WITH A FRIEND!! \n");
    printf(WHITE,"LETTERSIZE: CHANGES LETTER FONT \n");
    printf(WHITE,"CLEAR:      ERRASES THE TERMINAL :(\n");
    printf(WHITE,"TIME:       PRINTS CURRENT TIME IN ARGENTINA\n");
    printf(WHITE,"INFOREG:    TAKES A SNAPSHOT OF THE REGISTERS CONTENT\n");
    printf(WHITE,"MEMORY:     PRINTS THE MEMORY CONTENT OF 30 BYTES. YOU MUST SEND THE FIRST MEMORY PLACE BY PARAMETER.\n");
    printf(WHITE,"DIVIDEBYZERO: WANT TO KNOW WHAT HAPPENS WHEN YOU DIVIDE BY ZERO?\n");
    printf(WHITE,"OPCODE:     WANT TO KNOW WHAT HAPPENS WHEN YOU OP CODE?\n");
    printf(WHITE,"PIANO:      PLAY A PIANO WITH YOUR KEYBOARD!\n");
    printf(GREEN,"Hope you enjoy cacaTerminal!! \n");

    
      
   
}

void piano(){
    pianoPlay();
    clear();
}

void tron(){
    tronGame();
    clear();
}


int main() {
    setCharSize(1);
    printf(WHITE,"Welcome to cacaTerminal");
    hold(20);
    clear();


    while(1){
        hold(1);
        char c  = getChar();
        
        if (c != -1 && c!= 0){
            if(c == 8){ // 8 is ascii's basckspace  
                if(lineCantChar != 0){ 
                    backspace();
                    lineCantChar--;
                }
            } else if(c == '\n'){
                printf(WHITE,"\n");
                lineBuffer[lineCantChar] = 0;
                analizeCommand();
                
            }
            else{
                lineBuffer[lineCantChar++] = c;
                printChar(c, WHITE);
           
            }
        
        }
    }
    
}



