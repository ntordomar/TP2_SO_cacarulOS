#include <userStdF.h>
#include <userLib.h>

static char  regsCap[16][256];
static char captured = 0;



void inforeg(){

    if (captured == 0){
        printf(WHITE, "You need to screenshot with the arrow keys to print registers\n");
        return;
    }

    char * registersName[] = {"RDI", "RAX","RBX","RCX","RDX","RSI","RBP","RSP","R8","R9","R10","R11"
                             ,"R12","R13","R14","R15", "IP"};
    for (int i = 0; i<17; i++){
        printf(WHITE, "%s: %s \n" ,registersName[i],regsCap[i]);
    }
}

void capture() {
    captured = 1;
    itoa(getRDI(), (char *)regsCap[0], 10);
    int regs[16] = {0};
    getRegister(regs);
    for (int i = 0; i<16; i++){
        itoa(regs[i], (char *)regsCap[i+1], 10);
    }
}