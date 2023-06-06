// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <video.h>
#include <keyBoardHandler.h>
#include <lib.h>
#include <sync.h>
#include <pipe.h>

#define BUFFER_SIZE 1024

static char buff[BUFFER_SIZE] = {0}; // Defining a circular vector that we use as keyboard buffer

static int front = 0; // First iterator. Points to the front of the buffer
static int rear = 0;  // Second iterator. Points to the last element added
static int cantElems = 0;

static int controlFlag = 0;

int semId;

void keyboardHandlerInit()
{ // Initializes the keyboard handler
    semId = semCreate("keyboard", 0);
    semOpen("keyboard");
}

char nextElement()
{
    // returns the first element pushed into the buffer in cronological order
    semWait(semId);
    char toRet = buff[front];
    front++;
    cantElems--;
    return toRet;
}

// Every time someone presses a key this function gets called and inserts into the circular buffer
void keyHandler()
{
    int tecla = getKey();
    if (tecla == CTRL) // If ctrl was pressed, set the control flag to 1
    {
        controlFlag = 1;
        return;
    }
    else if (controlFlag) // If ctrl was pressed and then we press another key
    {
        switch (keyBoardTable[tecla])
        {
        case 'R':
            _snapshot_registers();
            break;
        case 'D':
            if (findPcbEntry(getForegroundProcess())->process->fd[0] != 0)
                sendEOFToCurrent();
            else
            {
                if (cantElems == BUFFER_SIZE)
                {
                    return;
                }
                if (rear == BUFFER_SIZE)
                    rear = 0; // Reposition of both the front and rear pointer
                if (front == BUFFER_SIZE)
                    front = 0;
                buff[rear++] = -1;
                cantElems++;
                semPost(semId);
            }
            break;
        case 'C':
            killCurrentForeground(semId);
            front = 0;
            rear = 0;
            cantElems = 0;
            break;
        }
        controlFlag = 0;

        return;
    }
    else if (tecla <= 0x79 && tecla > 0)
    { // 0x79 because its the code for the biggest 'press'. We do this to avoid getting the release of a key into the buffer

        if (cantElems == BUFFER_SIZE)
        {
            return;
        }
        if (rear == BUFFER_SIZE)
            rear = 0; // Reposition of both the front and rear pointer
        if (front == BUFFER_SIZE)
            front = 0;
        buff[rear++] = keyBoardTable[tecla];
        cantElems++;
        semPost(semId);
    }
}