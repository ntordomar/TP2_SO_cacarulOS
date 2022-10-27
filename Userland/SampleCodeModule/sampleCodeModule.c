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
    print("BIENVENIDOS A LA TERMINAL.", WHITE);
    newLine();
    print("Los comandos disponibles son:", WHITE);
    newLine();
    print("HELP, TRON, LETTERSIZE, CLEAR, TIME", WHITE);
    newLine();
    print("LETTERSIZE: ", WHITE);
    newLine();

}

void inforeg(int xPos, int yPos){
       char r2[256] = {0};
    itoa(getRDI(), r2, 10);
    print("RDI: ", WHITE);
    print(r2, WHITE);
    newLine();
    int regs[15];
    getRegisters(regs);
    char * registersName[] = {"RBX","RCX","RDX","RSI","RBP","RSP","R8","R9","R10","R11","R12","R13","R14","R15"};
    for (int i = 0; i<15; i++){
        char r[256] = {0};
        itoa(regs[i], r, 10);
        print(registersName[i],WHITE);
        print(r, WHITE);
        newLine();
    }
 

}


void tron(){
    tronGame();
    clear();
    resetTerminal();
    // xPos = 0;
    // yPos = 0;
}

// void backspace(){
//     if(xPos <= 0) {
//     if(yPos == 0) return;

//         xPos = 1024;
//         yPos -= 16 * initialCharSize;
//     } else {
//         xPos -= initialCharSize*8;
//     }
//     sys_write_char(xPos,yPos,' ',WHITE);
// }
    


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
// void clear(){
//     sys_clear_screen();
//     xPos = 0;
//     yPos = 0;
// }
// void newLine(){
//     xPos = 0;
//     yPos = yPos + initialCharSize * 16;
// }

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
        
       print(rta,WHITE);
    }
    
}


int main() {
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



