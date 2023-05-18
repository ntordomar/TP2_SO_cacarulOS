#include <userStdF.h>
#include <userLib.h>
#include <user_syscalls.h>

void inforeg(){
    
    int captured = 0;
    int regs[17] = {0};
    sys_get_regs(&captured, regs);

    if (captured == 0){
        printf(WHITE, "You need to screenshot with the CTRL key to capture the registers before printing them\n");
        return;
    }

    char * registersName[] = {"RAX","RBX","RCX","RDX","RSI","RDI","RBP","RSP","R8","R9","R10","R11"
                             ,"R12","R13","R14","R15", "RIP"};
    for (int i = 0; i<17; i++){
        printf(WHITE, "en formato decimal %s: %d \n" ,registersName[i],regs[i]);
        printf(WHITE, "en formato hexadecimal  %s: %x \n" ,registersName[i],regs[i]);
    }
}

