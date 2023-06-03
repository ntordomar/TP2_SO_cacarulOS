#include <video.h>
#include <keyBoardHandler.h>
#include <lib.h>
#include <sync.h>

#define BUFFER_SIZE 1024

static char buff[BUFFER_SIZE] = {0}; // Defining a circular vector that we use as keyboard buffer

static int front = 0; // First iterator. Points to the front of the buffer
static int rear = 0;  // Second iterator. Points to the last element added
static int cantElems = 0;

int semId;

void keyboardHandlerInit()
{ // Initializes the keyboard handler
    semId = semCreate("keyboard", 0);
    semOpen("keyboard");
}

char nextElement()
{ // returns the first element pushed into the buffer in cronological order
    // if (cantElems == 0)
    //     return -1;
    semWait(semId);
    char toRet = buff[front];
    front++;
    cantElems--;
    return toRet;
}

void keyHandler(int tecla)
{ // Every time someone presses a key this function gets called and inserts into the circular buffer

    if (tecla <= 0x79)
    { // 0x79 because its the code for the biggest 'press'. We do this to avoid getting the releas of a key into the buffer

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