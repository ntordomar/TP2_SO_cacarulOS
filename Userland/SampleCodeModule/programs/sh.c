

#include <userLib.h>
#include <stdint.h>
#include <tron.h>
#include <piano.h>
#include <inforeg.h>
#include <time.h>
#include <memory.h>
#include <lettersize.h>
#include <exceptions.h>
#include <drawings.h>
#include <user_syscalls.h>
#include <stddef.h>
#include <userlandApps.h>

void analizeCommand();

static int commandCount = 13;
static char lineBuffer[1024] = {0};
static int lineCantChar = 0;

static char *commandList[] = {"HELP", "LETTERSIZE", "CLEAR", "TIME", "INFOREG", "MEMORY", "DIVIDEBYZERO", "OPCODE", "PS", "LOOP", "KILL", "NICE", "BLOCK"};
static int (*commandFunctions[])(char **param) = {help, lettersize, clear, time, inforeg, memory, divideByZero, opCode, ps, loop, kill, nice, block};

void analizeCommand()
{

    // si hay un pipe en el string
            //


    
    // Si hay un & en el string
            //

    // sino, el caso normal que ya funca

    char argument[50];
    char argument2[50];
    divideString(lineBuffer, argument, ' ');
    divideString(argument, argument2, ' ');



    for (int i = 0; i < commandCount; i++)
    {
        if (strcmp(lineBuffer, commandList[i]) == 0)
        { // If theres a match, the command function gets called

            char **args;
            args = sys_malloc(3 * sizeof(char *), args); // CAMBIAR A QUE NO SEA LA SYSCALL!
            args[0] = sys_malloc(50, args[0]);
            strcpy(args[0], argument);
            args[1] = sys_malloc(50, args[1]);
            strcpy(args[1], argument2);
            args[2] = NULL;
            sys_create_process(commandList[i], args, commandFunctions[i], 1);
            // (*commandFunctions[i])(argument); // CAMBIAR A CREAR UN PROCESO CON EL CODIGO
            lineCantChar = 0;

            return;
        }
    }

    printf(WHITE, "%s COMMAND NOT FOUND\n", lineBuffer);
    lineCantChar = 0;
}

void sh()
{
    setCharSize(3);
    setCursorPosition(270, 250);
    // printf(WHITE, "Welcome to cacarulOS");
    // cacarulo(430, 400);
    setCharSize(1);
    clear();
    printf(WHITE, "Welcome to cacarulo's terminal. To see available commands, write HELP, followed by an enter.");
    hold(60);
    clear();
    printf(WHITE, "root@cacarulOS $ ");
    while (1)
    {

        char c = getChar(); // We continously ask if there is a new char to print

        if (c != -1 && c != 0)
        {
            if (c == 8)
            { // 8 is ascii's basckspace
                if (lineCantChar != 0)
                {
                    backspace();
                    lineCantChar--;
                }
            }
            else if (c == '\n')
            {
                printf(WHITE, "\n");
                lineBuffer[lineCantChar] = 0;
                analizeCommand();
                printf(WHITE, "root@cacarulOS $ ");
            }
            else
            {
                lineBuffer[lineCantChar++] = c;
                printChar(c, WHITE);
            }
        }
    }
}