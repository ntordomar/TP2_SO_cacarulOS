#include <pipe.h>
#include <sync.h>

pipeType pipeArray[MAX_PIPES];

int maxPipeName = 1;

void pipeInit()
{
    pipeArray[0].name = 0; // Set the first position to 0 for the shell

    for (int i = 1; i < MAX_PIPES; i++)
    {
        pipeArray[i].name = -1;
    }
}

pipe_t pipeCreateWithName(int name)
{
    int freeSpace = 0;
    for (int i = 1; i < MAX_PIPES && freeSpace == 0; i++)
    {
        if (pipeArray[i].name == -1)
        {
            freeSpace = i;
        }

        if (pipeArray[i].name == name)
        {
            return -1;
        }
    }

    // in free space we have the first unused pipe of the array
    pipeArray[freeSpace].name = name;
    pipeArray[freeSpace].readPos = 0;
    pipeArray[freeSpace].writePos = 0;
    pipeArray[freeSpace].eof = 0;
    pipeArray[freeSpace].leftToRead = 0;

    // Set the semaphore names
    pipeArray[freeSpace].readSemId = semCreateAnonymous(0);
    pipeArray[freeSpace].writeSemId = semCreateAnonymous(BUFFER_PIPE_SIZE);

    pipeArray[freeSpace].pipeBuffer = (char *) malloc(BUFFER_PIPE_SIZE);

    if (name > maxPipeName)
    {
        maxPipeName = name + 1;
    }
    return freeSpace;
}

pipe_t pipeCreateAnonymous()
{
    return pipeCreateWithName(maxPipeName);
}

int pipeWrite(pipe_t id, const char *src, unsigned int count)
{

    for (int i = 0; i < count; i++)
    {
        semWait(pipeArray[id].writeSemId);

        if (pipeArray[id].writePos == BUFFER_PIPE_SIZE)
        {
            pipeArray[id].writePos = 0;
        }
        
        pipeArray[id].pipeBuffer[pipeArray[id].writePos++] = (char) src[i];
        pipeArray[id].leftToRead++;
        semPost(pipeArray[id].readSemId);
    }
}

int pipeRead(pipe_t id, char *dest, unsigned int count)
{
    if (pipeArray[id].eof && pipeArray[id].leftToRead == 0)
    {
        return -1;
    }

    for (int i = 0; i < count; i++)
    {
        semWait(pipeArray[id].readSemId);

        if (pipeArray[id].readPos == BUFFER_PIPE_SIZE)
        {
            pipeArray[id].readPos = 0;
        }

        dest[i] = pipeArray[id].pipeBuffer[pipeArray[id].readPos++];
        pipeArray[id].leftToRead--;
        semPost(pipeArray[id].writeSemId);
    }
}

void pipeDestroy(pipe_t id)
{
    pipeArray[id].name = -1;
    pipeArray[id].readPos = 0;
    pipeArray[id].writePos = 0;
    pipeArray[id].eof = 0;

    semDestroy(pipeArray[id].readSemId);
    semDestroy(pipeArray[id].writeSemId);
    free(pipeArray[id].pipeBuffer);
}

void sendEOFSignal(pipe_t id)
{
    pipeArray[id].eof = 1;
}

pipe_t getPipeIdByName(int name)
{

    for (int i = 0; i < MAX_PIPES; i++)
    {
        if (pipeArray[i].name == name)
        {
            return i;
        }
    }
    return -1;
}