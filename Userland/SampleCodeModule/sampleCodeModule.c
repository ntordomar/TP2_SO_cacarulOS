/* sampleCodeModule.c */
// terminal
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
void inforeg();
void memory(char * param);

char * v = (char*)0xB8000 + 79 * 2;

// static int yPos = 0;
// static int xPos = 0;

static char* commandList[] = {"HELP", "TRON", "LETTERSIZE","CLEAR", "TIME", "INFOREG", "MEMORY"};
static void (*commandFunctions[7])(char * param) = {help, tron, lettersize, clear, time, inforeg, memory};

static int commandCount = 7;

static char lineBuffer[256] = {0}; //ir completando a medida que sigamos en la misma 
static lineCantChar = 0;

int isDigit(char c){
    return c >= '0' && c<= '9';
}

void analizeCommand(){ // int strcmp 0 si si 1 sino
    //Aca la linea seria comando 2
    char argument[50];
    divideString(lineBuffer,argument,' ');
    for (int i =0; i<commandCount; i++){
        if (strcmp(lineBuffer, commandList[i]) == 0){
            (*commandFunctions[i])(argument);
            lineCantChar = 0;
        
            return;
        } 
    }
    print(lineBuffer, WHITE);
    print(" COMMAND NOT FOUND", WHITE);
    newLine();
    lineCantChar = 0;
    
}

void time(){
    print("TIEMPO ACTUAL:", WHITE);
    newLine();
    printCurrentTime();
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
 printf(GREEN,"Welcome to cacaHELP The following available commands are:\n\n\n\n\n\n");
 printf(GREEN,  "COMMAND name:   USE:\n");
 printf(WHITE,"HELP:       SHOWS YOU THE AVAILABLE COMMANDS, AND THEIR USAGE\n");
printf(WHITE, "TRON:       PLAY TRON WITH A FRIEND!! \n");
 printf(WHITE,"LETTERSIZE: CHANGES LETTER FONT \n");
 printf(WHITE,"CLEAR:      ERRASE THE TERMINAL :(\n");
 printf(WHITE,"TIME:       PRINTS CURRENT TIME IN ARGENTINA\n");
 printf(WHITE,"INFOREG:    TAKES A SNAPSHOT OF THE REGISTERS CONTENT\n");
 printf(WHITE,"MEMORY:     PRINTS THE MEMORY CONTENT OF 30 BYTES. YOU MUST SEND THE FIRST MEMORY PLACE BY PARAMETER.\n");
printf(GREEN,"\nHope you\n enjoy cacaTerminal!! \n");

}

void inforeg(int xPos, int yPos){
    char r2[256] = {0};
    itoa(getRDI(), r2, 10);
    print("RDI: ", WHITE);
    print(r2, WHITE);
    newLine();
    int regs[15];
    getRegisters(regs);
    char * registersName[] = {"RAX","RBX","RCX","RDX","RSI","RBP","RSP","R8","R9","R10","R11"
                                ,"R12","R13","R14","R15"};
    for (int i = 0; i<15; i++){
        char r[256] = {0};
        itoa(regs[i], r, 10);
        printf(WHITE, "%s: %s \n" ,registersName[i],r);
    }
 

}


void tron(){
    tronGame();
    clear();
    resetTerminal();
    // xPos = 0;
    // yPos = 0;
}


void lettersize() {
    print("Write a number", WHITE);
    // sys_write(xPos, yPos, "Ingrese un numerito", 19, WHITE);
    // xPos+=initialCharSize*8;
    newLine();
    char buff[50];
    int buffPos = 0;
    char c;

    while(1){
         
        c = getc();  
        if (c!=-1 && c!=0){
    //for(int i = 0; i<9000; i++);
            hold(1);
            if(c == '\n'){
                newLine();
                buff[buffPos] = 0;
                setCharSize(myAtoi(buff));
                // sys_change_font_size(myAtoi(buff));
                // initialCharSize = myAtoi(buff);
                // sys_write(xPos,yPos,"SE HA CAMBIADO EL NUMERITO",26,WHITE);
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

void memory(char * param) {
    if (strlen(param) == 0) {
        print("Error: mising a parameter. Must indicate memory direction.", WHITE);
        newLine();
        return;
    }

    int memoryPos = myAtoi(param);
    unsigned char mem[32];
   
    getMemory(memoryPos, mem);
    for(int i = 0; i< 32; i++){
        char rta[256] = {0};
        itoa(mem[i],rta,10);
        printf(WHITE, "Direccion %d: %c \n", memoryPos + i, rta);
    }
    
}


int main() {
    setCursorPosition(20, 20);
    printf("Hola %d \n %d", 20, 10);
    resetTerminal();
    //sys_write_char(20, 20, 'A', WHITE);
    // newLine();
    // lineBuffer[lineCantChar] = 0;
    while(1){
        // hold(1); //NO FUNCIONA CON HOLD ?
        char c  = getc();
        for(int i = 0; i< 9000; i++){;}
        
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
                printChar(c, WHITE);
            //    sys_write_char(xPos, yPos, c, WHITE);
            //    xPos +=initialCharSize*8;
            }
        
        }
    }
    
}



