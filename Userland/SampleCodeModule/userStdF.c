#include <user_syscalls.h>
#include <userStdF.h>
static int buffPos = 0;
char getc(){
    char localBuff[1];
    sys_read(&localBuff, 1);
    return localBuff[0];
}