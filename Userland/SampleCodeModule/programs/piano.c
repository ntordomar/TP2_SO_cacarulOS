#include <user_syscalls.h>
#include <userStdF.h>
#include <piano.h>
void pianoPlay(){
    resetTerminal();
    printf(WHITE, "The notes are: s(C) d(D) f(E) g(F) h(G) j(A) k(B) \n");
    printf(GREEN, "press o  if you want to learn how to play 'Himno de la alegria'\n");
    printf(WHITE, "press x  to exit'\n");
    char c;
    while(1){
        hold(1);
        c = getChar();
        switch (c)
        {
        case 'S':
            sys_beep(130, 5);
            break;
        case 'D':
            sys_beep(146, 5);
            break;
        case 'F':
            sys_beep(164, 5);
            break;
        case 'G':
            sys_beep(174, 5);
            break;
        case 'H':
            sys_beep(196, 5);
            break;
        case 'J':
            sys_beep(220, 5);
            break;
        case 'K':
            sys_beep(246, 5);
            break;
        case 'O':
            printf(GREEN, "\nK K S D D S K J H H J K K J J\nK K S D D S K J H H J K J H H\n");
            break;
        case 'X':
            return;
    }
}
}