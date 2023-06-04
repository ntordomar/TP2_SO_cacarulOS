#include <userlandApps.h>
// #include <userStdF.h>

int help(char ** args)
{
    printf(GREEN, "Welcome to cacarulOS help. The following available commands are:\n\n\n");
    printf(GREEN, "COMMAND name:   USE:\n");
    printf(WHITE, "HELP:           SHOWS YOU THE AVAILABLE COMMANDS, AND THEIR USAGE\n");
    printf(WHITE, "TRON:           PLAY TRON WITH A FRIEND!! \n");
    printf(WHITE, "LETTERSIZE:     CHANGES LETTER FONT \n");
    printf(WHITE, "CLEAR:          CLEARS THE SCREEN TERMINAL \n");
    printf(WHITE, "TIME:           PRINTS CURRENT TIME GTC\n");
    printf(WHITE, "INFOREG:        TAKES A SNAPSHOT OF THE REGISTERS CONTENT. YOU MUST TAKE A SCREENSHOT BEFORE WITH CTRL KEY.\n");
    printf(WHITE, "MEMORY:         PRINTS THE MEMORY CONTENT OF 30 BYTES. YOU MUST SEND THE FIRST MEMORY PLACE BY PARAMETER.\n");
    printf(WHITE, "DIVIDEBYZERO:   WANT TO KNOW WHAT HAPPENS WHEN YOU DIVIDE BY ZERO?\n");
    printf(WHITE, "OPCODE:         WANT TO KNOW WHAT HAPPENS WHEN YOU OP CODE?\n");
    printf(WHITE, "PIANO:          PLAY A PIANO WITH YOUR KEYBOARD!\n");
    printf(GREEN, "Hope you enjoy the cacarulOS!! \n");
    return 0;
}
