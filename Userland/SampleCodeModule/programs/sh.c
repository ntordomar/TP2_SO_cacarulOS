

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


static int commandCount = 17;
static char lineBuffer[1024] = {0};
static int lineCantChar = 0;

static char *commandList[] = {"HELP", "LETTERSIZE", "CLEAR", "TIME", "INFOREG", "MEMORY", "DIVIDEBYZERO", "OPCODE", "PS", "LOOP", "KILL", "NICE", "BLOCK", "MEM","TESTPROCESS", "CAT","FILTER"};
static int (*commandFunctions[])(char **param) = {help, lettersize, clear, time, inforeg, memory, divideByZero, opCode, ps, loop, kill, nice, block, mem,test_processes, cat,filter};


int findAndExecProcess(char * command, char * arg1, char * arg2, char fg){
    for (int i = 0; i < commandCount; i++)
        {
            if (strcmp(lineBuffer, commandList[i]) == 0)
            { 
                char **args;
                args = sys_malloc(3 * sizeof(char *), args); 

                if (arg1 != NULL){
                    args[0] = sys_malloc(50, args[0]);
                    strcpy(args[0], arg1);
                } else args[0] = NULL;

                if (arg2 != NULL){
                    args[1] = sys_malloc(50, args[1]);
                    strcpy(args[1], arg2);
                } else args[1] = NULL;
            
                args[2] = NULL;
                int pid = sys_create_process(commandList[i], args, commandFunctions[i], fg);
            
                if (pid == -1){
                    printf(WHITE, "Could not create process \n");
                } else {
                    sys_waitpid(pid);
                }
                lineCantChar = 0;
                return pid;
            }
        }
    
    printf(WHITE, "%s not found \n",command);
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

    char bg = 0;

    if (lineBuffer[lineCantChar -1] == ';'){
        bg = 1;
    }

    if (foundPipe) {
        char command1[50] = {0};    
        char command2[50] = {0};
        divideString(lineBuffer, command1, '/');
        divideString(command1, command2, ' ');

        int pid = findAndExecProcess(lineBuffer, NULL, NULL, 1);
        if (pid != -1){
            int pid2 = findAndExecProcess(command1, NULL, NULL, 1);
        }
    } else {
        char arg1[50] = {0};    
        char arg2[50] = {0};
        divideString(lineBuffer, arg1, ' ');
        divideString(arg1, arg2, ' ');
        int pid = findAndExecProcess(lineBuffer, arg1, arg2, 1);
    }
    
    
    


    //Caso 2: Existe un & en el texto
        //Agarro el texto hasta el & y busco proc con ese nombre


}

int sh()
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
    return 0;
}