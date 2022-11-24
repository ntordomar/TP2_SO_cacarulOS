#include <userStdF.h>
#include <userLib.h>
#include <memory.h>
#include <user_syscalls.h>

void memory(char * param) {
    if (strlen(param) == 0) {
        print("Error: mising a parameter. Must indicate memory direction.", WHITE);
        newLine();
        return;
    }

    int memoryPos = atoi(param);
    unsigned char mem[32];
   
    sys_get_mem(memoryPos, mem);
    
    for(int i = 0; i< 32; i++){
        char rta[4] = {0};
        itoa(mem[i],rta,10);
        printf(WHITE, "Direccion %d: %s \n", memoryPos + i, rta);
    }
    
}