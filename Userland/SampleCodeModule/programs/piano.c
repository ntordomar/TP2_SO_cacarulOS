#include <user_syscalls.h>
#include <userStdF.h>

void painoPlay(){
    char c;
    while(1){
        hold(1);
        c = getChar();
        switch (c)
        {
        case 'S':
            printf(RED,"HOLA");
            sys_beep(130, 10);
            break;
        case 'D':
            sys_beep(146, 10);
            break;
        case 'F':
            sys_beep(164, 10);
            break;
        case 'G':
            sys_beep(174, 10);
            break;
        case 'H':
            sys_beep(196, 10);
            break;
        case 'J':
            sys_beep(220, 10);
            break;
        case 'K':
            sys_beep(246, 10);
            break;
        case 'X':
            return;
    }
}
}