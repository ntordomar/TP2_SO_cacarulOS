#include <userStdF.h>
#include <userLib.h>

void inforeg(){
    
    int captured = 0;
    int regs[17] = {0};
    sys_get_regs(&captured, regs);

    if (captured == 0){
        printf(WHITE, "You need to screenshot with the CTRL key to capture the registers before printing them\n");
        return;
    }

    char * registersName[] = {"RDI", "RAX","RBX","RCX","RDX","RSI","RBP","RSP","R8","R9","R10","R11"
                             ,"R12","R13","R14","R15", "IP"};
    for (int i = 0; i<17; i++){
        printf(WHITE, "%s: %s \n" ,registersName[i],regs[i]);
    }
}

