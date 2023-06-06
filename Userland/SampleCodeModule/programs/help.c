// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <userlandApps.h>

int help(char ** args)
{
    printf(GREEN, "---WELCOME TO THE CACARULOS HELP---");
    printChar('\n', WHITE);
    printf(WHITE, "TO RUN A PROCESS YOU HAVE TO TYPE THEIR COMMAND IN THE TERMINAL AND PRESS ENTER");
    printChar('\n', WHITE);
    printf(WHITE, "-> BY DEFAULT, PROCESSES RUN IN FOREGROUND. IF YOU WANT TO RUN IT IN BACKGROUND YOU MUST TYPE AS A LAST PARAMETER ';'");
    printChar('\n', WHITE);
    printf(CREME, "   EXAMPLE: 'HELP ;'");
    printChar('\n', WHITE);
    printf(WHITE, "-> YOU CAN ALSO PIPE TWO PROCESSES. TO DO SO YOU HAVE TO TYPE THE COMMANDS JOINED BY A '/' (WITH NO SPACES BETWEEN)");
    printChar('\n', WHITE);
    printf(CREME, "   EXAMPLE: 'HELP/FILTER'");
    printChar('\n', WHITE);
    printf(BLUE, "TO STOP A PROCESS FROM RUNNING, YOU HAVE TO PRESS CTRL + C");
    printChar('\n', WHITE);
    printf(BLUE, "TO SEND AN EOF, YOU HAVE TO PRESS CTRL + D\n");
    printChar('\n', WHITE);
    printf(WHITE, "THE PROCESSES AND THEIR COMMANDS ARE SHOWN BELOW:");
    printChar('\n', WHITE);
    printf(GREEN, "COMMAND NAME:      USE:");
    printChar('\n', WHITE);
    printf(WHITE, "HELP:              SHOWS YOU THE AVAILABLE COMMANDS, AND THEIR USAGE");
    printChar('\n', WHITE);
    printf(WHITE, "TRON:              PLAY TRON WITH A FRIEND!!");
    printChar('\n', WHITE);
    printf(WHITE, "LETTERSIZE:        CHANGES LETTER FONT");
    printChar('\n', WHITE);
    printf(WHITE, "CLEAR:             CLEARS THE SCREEN TERMINAL");
    printChar('\n', WHITE);
    printf(WHITE, "MEMORY:            PRINTS THE MEMORY CONTENT OF 30 BYTES. YOU MUST SEND THE FIRST MEMORY PLACE BY PARAMETER.");
    printChar('\n', WHITE);
    printf(WHITE, "OPCODE:            WANT TO KNOW WHAT HAPPENS WHEN YOU OP CODE?");
    printChar('\n', WHITE);
    printf(WHITE, "PIANO:             PLAY A PIANO WITH YOUR KEYBOARD!");
    printChar('\n', WHITE);
    printf(WHITE, "MEM:               PRINTS THE CURRENT STATE OF THE HEAP MEMORY");
    printChar('\n', WHITE);
    printf(WHITE, "PS:                PRINTS A LIST WITH ALL THE PROCESSES AND THEIR PROPERTIES");
    printChar('\n', WHITE);
    printf(WHITE, "LOOP:              PRINTS THE CURRENT'S PROCESS ID WITH A GREETING");
    printChar('\n', WHITE);
    printf(WHITE, "KILL:              KILLS A PROCESS GIVEN ITS ID");
    printChar('\n', WHITE);
    printf(WHITE, "NICE:              CHANGES A PROCESS'S PRIORITY GIVEN ITS ID AND THE NEW PRIORITY");
    printChar('\n', WHITE);
    printf(WHITE, "BLOCK:             CHANGES THE STATE OF A PROCESS BETWEEN BLOCKED AND READY GIVEN ITS ID");
    printChar('\n', WHITE);
    printf(WHITE, "CAT:               PRINTS THE STANDARD INPUT");
    printChar('\n', WHITE);
    printf(WHITE, "WC:                COUNTS THE AMOUNT OF LINES FROM THE INPUT AFTER AND EOF IS SENT");
    printChar('\n', WHITE);
    printf(WHITE, "PHYLO:             SHOWS THE DINING PHILOSOPHERS PROBLEM");
    printChar('\n', WHITE);
    printf(GOLD, "~TESTS~");
    printChar('\n', WHITE);
    printf(WHITE, "TESTMEM:         TESTS ALLOCATION AND FREE OF MEMORY WHEN RECIEVING A SIZE OF A MEMORY BLOCK (AS A PARAMETER)");
    printChar('\n', WHITE);
    printf(WHITE, "TESTPROCESS:     TESTS CREATION AND DESTRUCTION OF A MAXIMUM QUANTITY OF PROCESSES (AS A PARAMETER)");
    printChar('\n', WHITE);
    printf(WHITE, "TESTPRIO:        TESTS PRIORITY IMPLEMENTATION AND CHANGES BETWEEN PROCESSES");
    printChar('\n', WHITE);
    printf(WHITE, "TESTSEM:         TESTS CREATION, OPENING, CLOSING AND DESTRUCTION OF A MAXIMUM QUANTITY OF SEMAPHORES (AS A PARAMETER)");
    printChar('\n', WHITE);
    printf(WHITE, "                 NEEDS A SECOND PARAMETER: A 1 IF YOU WANT IT TO USE SYNCRONIZATION AND A 0 IF YOU DON'T\n");
    printChar('\n', WHITE);

    printf(GREEN, "HOPE YOU ENJOY THE CACARULOS!");
    printChar('\n', WHITE);
    return 0;
}
