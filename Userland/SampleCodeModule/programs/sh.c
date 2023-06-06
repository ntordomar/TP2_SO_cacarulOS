// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com


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

static int commandCount = 20;
static char lineBuffer[1024] = {0};
static int lineCantChar = 0;

static char *commandList[] = {"HELP", "LETTERSIZE", "CLEAR", "DIVIDEBYZERO", "OPCODE", "PS", "LOOP", "KILL", "NICE", "BLOCK", "MEM", "TESTPROCESS", "CAT", "FILTER", "WC","PHYLO", "TESTSEM", "TESTPRIO", "TESTMEM"};
static int (*commandFunctions[])(char **param) = {help, lettersize, clear, divideByZero, opCode, ps, loop, kill, nice, block, mem, test_processes, cat, filter, wc, phylo, test_sync, test_prio, test_mem};

int fds[2] = {0, 0};



int createPipedProcess(char ** args) {
    if(args[0] == NULL || args[1] == NULL) return -1;
    int pipeFd = pipeCreateAnonymous();
    int *fds1 = (int *)malloc(2 * sizeof(int));
    if(fds1 == NULL) 
    {
        return -1;
    }
    int *fds2 = (int *)malloc(2 * sizeof(int));
    if(fds2 == NULL)
    {
        free(fds1);
        return -1;
    }
    fds2[0] = pipeFd;
    fds2[1] = 0;
    fds1[0] = 0;
    fds1[1] = pipeFd;
    int pid1 = findAndExecProcess(args[0],1,fds1);
    int pid2 = findAndExecProcess(args[1],1,fds2);
 
    sys_waitpid(pid1);
    killProcess(pid2);
    killProcess(pid2);
    return 0;
}

int findAndExecProcess(char * line, char piped, int *fds)
{
    char isForeground = 1;
    if(piped)
    {
        isForeground = 0;
    }
    
    char arg1[50] = {0};
    char arg2[50] = {0};

    int i=0;
    while(line[i] != 0)
    {
        i++;
    }

    if (line[i - 1] == ';')
    {
        isForeground = 0;
        divideString(line, arg2, ';');
    }
    
    divideString(line, arg1, ' ');
    divideString(arg1, arg2, ' ');
    
    for (int i = 0; i < commandCount; i++)
    {
        if (strcmp(line, commandList[i]) == 0)
        {
            char **args;
            args = malloc(3 * sizeof(char *));
            if(args == NULL)
            {
                return -1;
            }

            if (arg1[0] != 0)
            {
                args[0] = malloc(50);
                if(args[0] == NULL)
                {
                    free(args);
                    return -1;
                }
                strcpy(args[0], arg1);
            }
            else
                args[0] = NULL;

            if (arg2[0] != 0 )
            {
                args[1] = malloc(50);
                if(args[1] == NULL)
                {
                    free(args);
                    return -1;
                }
                strcpy(args[1], arg2);
            }
            else
            {
                args[1] = NULL;
            }

            args[2] = NULL;
            int pid = sys_create_process(commandList[i], args, commandFunctions[i], isForeground, fds);

            if (pid == -1)
            {
                printf(WHITE, "Could not create process \n");
            }else
            {
                if(isForeground)
                {
                    sys_waitpid(pid);
                }
            }
            lineCantChar = 0;
            return pid;
        }
    }

    printf(WHITE, "%s not found \n", line);
    lineCantChar = 0;
    return 0;
}

void analizeCommand()
{
    int i = 0;
    int foundPipe = 0;
    
    while (i < lineCantChar && !foundPipe)
    {
        if (lineBuffer[i] == '/')
        {
            foundPipe = 1;
        }
        i++;
    }

    int *fds = (int *) malloc(2*sizeof(int));
    if(fds == NULL)
    {
        return;
    }

    fds[0]= 0;
    fds[1] = 0;
    
    if (foundPipe)
    {
        char command1[50] = {0};
        divideString(lineBuffer, command1, '/');
        char ** args = malloc(3 * sizeof(char *));
        if(args == NULL)
        {
            free(fds);
            return;
        }

        args[0] = malloc(50);
        if(args[0] == NULL)
        {
            free(args);
            free(fds);
            return;
        }
        strcpy(args[0], lineBuffer);
        args[1] = malloc(50);
        if(args[1]==NULL)
        {
            free(args);
            free(fds);
            return;
        }
        strcpy(args[1], command1);
        args[2] = NULL;


        int pipePid = sys_create_process("PipedProcess", args, &createPipedProcess, 1, fds);
        sys_waitpid(pipePid);
    }
    else
    {
        findAndExecProcess(lineBuffer,0,fds);
    }
}

int sh()
{
    setCharSize(3);
    setCursorPosition(270, 250);
    printf(WHITE, "Welcome to cacarulOS");
    cacarulo(430, 400);
    setCharSize(1);
    clear(NULL);
    printf(WHITE, "Welcome to cacarulo's terminal. To see available commands, write HELP, followed by an enter.");
    hold(60);
    clear(NULL);
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