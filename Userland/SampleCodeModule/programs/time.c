// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <userStdF.h>
#include <user_syscalls.h>

void printCurrentTime() {
    int  seconds, minutes, hours;
    sys_get_seconds(&seconds);
    sys_get_minutes(&minutes);
    sys_get_hours(&hours); 
    printf(WHITE, "%x : %x : %x",hours,minutes,seconds);
}
void time(){
    printf(WHITE,"CURRENT TIME (GMT): \n");
    printCurrentTime();
    printf(WHITE,"\n");
} 
