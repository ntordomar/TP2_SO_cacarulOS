#include <userStdF.h>


void printCurrentTime() {
    int  seconds, minutes, hours;
    sys_get_seconds(&seconds);
    sys_get_minutes(&minutes);
    sys_get_hours(&hours); 
    printf(WHITE, "%x : %x : %x",hours-6-3,minutes,seconds);
}
void time(){
    printf(WHITE,"TIEMPO ACTUAL: \n");
    printCurrentTime();
    printf(WHITE,"\n");
} 
