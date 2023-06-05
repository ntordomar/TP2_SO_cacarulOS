

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

static int commandCount = 19;
static char lineBuffer[1024] = {0};
static int lineCantChar = 0;

static char *commandList[] = {"HELP", "LETTERSIZE", "CLEAR", "TIME", "INFOREG", "MEMORY", "DIVIDEBYZERO", "OPCODE", "PS", "LOOP", "KILL", "NICE", "BLOCK", "MEM", "TESTPROCESS", "CAT", "FILTER", "WC","PHYLO"};
static int (*commandFunctions[])(char **param) = {help, lettersize, clear, time, inforeg, memory, divideByZero, opCode, ps, loop, kill, nice, block, mem, test_processes, cat, filter, wc, phylo};

int fds[2] = {0, 0};

int findAndExecProcess(char *command, char *arg1, char *arg2, char fg, int *fds)
{
    for (int i = 0; i < commandCount; i++)
    {
        if (strcmp(command, commandList[i]) == 0)
        {
            char **args;
            args = sys_malloc(3 * sizeof(char *), args);

            if (arg1 != NULL)
            {
                args[0] = sys_malloc(50, args[0]);
                strcpy(args[0], arg1);
            }
            else
                args[0] = NULL;

            if (arg2 != NULL)
            {
                args[1] = sys_malloc(50, args[1]);
                strcpy(args[1], arg2);
            }
            else
                args[1] = NULL;

            args[2] = NULL;
            int pid = sys_create_process(commandList[i], args, commandFunctions[i], fg, fds);

            if (pid == -1)
            {
                printf(WHITE, "Could not create process \n");
            }
            else
            {
                // sys_waitpid(pid);
            }
            lineCantChar = 0;
            return pid;
        }
    }

    printf(WHITE, "%s not found \n", command);
    lineCantChar = 0;
    return 0;
}

void analizeCommand()
{
    int i = 0;
    int foundPipe = 0;
    
    char isForeground = 1;
    while (i < lineCantChar && !foundPipe)
    {
        if (lineBuffer[i] == '/')
        {
            foundPipe = 1;
        }
        i++;
    }

    if (lineBuffer[lineCantChar - 1] == ';')
    {
        isForeground = 0;
    }

    if (foundPipe)
    {
        char command1[50] = {0};
        char command2[50] = {0};
        divideString(lineBuffer, command1, '/');
        divideString(command1, command2, ' ');

        // crear el pipe
        int pipeFd = pipeCreateAnonymous();
        int *fds1 = (int *)malloc(2 * sizeof(int));
        int *fds2 = (int *)malloc(2 * sizeof(int));
        fds2[0] = pipeFd;
        fds2[1] = 0;
        fds1[0] = 0;
        fds1[1] = pipeFd;
        int pid = findAndExecProcess(lineBuffer, NULL, NULL, isForeground, fds1);
        if (pid != -1)
        {
            int pid2 = findAndExecProcess(command1, NULL, NULL, isForeground, fds2);
            if (pid2 != -1)
            {
                sys_waitpid(pid2);
                killProcess(pid);
                // lineCantChar = 0;
                // lineBuffer[lineCantChar] = 0;
                // newLine();
            }
        }
    }
    else
    {
        char arg1[50] = {0};
        char arg2[50] = {0};
        divideString(lineBuffer, arg1, ' ');
        divideString(arg1, arg2, ' ');
        int pid = findAndExecProcess(lineBuffer, arg1, arg2, isForeground, fds);
        if (pid != -1)
        {
            sys_waitpid(pid);
            // lineCantChar = 0;
            // lineBuffer[lineCantChar] = 0;
            // newLine();
        }
    }

    // Caso 2: Existe un & en el texto
    // Agarro el texto hasta el & y busco proc con ese nombre
}

int sh()
{
    setCharSize(3);
    setCursorPosition(270, 250);
    // printf(WHITE, "Welcome to cacarulOS");
    // cacarulo(430, 400);
    setCharSize(1);
    // clear();
    // printf(WHITE, "Welcome to cacarulo's terminal. To see available commands, write HELP, followed by an enter.");
    // hold(60);
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
    return 0;
}