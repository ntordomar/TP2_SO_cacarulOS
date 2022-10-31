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
            sys_beep(130, 1);
            break;
        case 'D':
            sys_beep(146, 1);
            break;
        case 'F':
            sys_beep(164, 1);
            break;
        case 'G':
            sys_beep(174, 1);
            break;
        case 'H':
            sys_beep(196, 1);
            break;
        case 'J':
            sys_beep(220, 1);
            break;
        case 'K':
            sys_beep(246.9, 1);
            break;
    }
}
}