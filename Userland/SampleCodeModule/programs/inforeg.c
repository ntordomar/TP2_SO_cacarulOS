#include <userStdF.h>

void inforeg(){
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