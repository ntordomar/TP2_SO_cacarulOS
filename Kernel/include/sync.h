#include <queueADT.h>
#include "./process.h"
// Se abre y me uno con el nombre
// cuando se abre un semaphore se agrega a la primer posicion del vector libre

// Semaphore.h

typedef int sem_t;

#define SEM_MAX 200
#define FIRST_USER_SEM 100

typedef struct
{
    char *name;
    Queue *blockedProcesses;
    size_t value;
    char activeProcesses[MAX_CANT_PROCESSES]; // Keeps track of the processes that have permission to access the semaphore
    char destroying;
    int destroyerPID;
    size_t activeProcessCant;
} semaphoreType;

sem_t semCreate(char *name, int initValue); // Adds a new semaphore to the array
sem_t semOpen(char *name);                  // Opens an existing semaphore
int semClose(sem_t semId);                  // Closes the semaphore. returns 0 if success, -1 if error
int semDestroy(sem_t semId);                // Destroys the semaphore. returns 0 if success, -1 if error
int semWait(sem_t semId);                   // Decrements semaphore, or blocks process if semaphore is 0
int semPost(sem_t semId);                   // Increments semaphore
void semInit();                             // Initializes the semaphore array
int semSet(int semId, int value);           // Sets the value of the semaphore
sem_t semCreateAnonymous(int initValue);    // Creates an anonymous semaphore

typedef int mutex_t;

typedef struct mutexType
{
    Queue *blockedProcesses;
    char value; // only 1 or 0
    int currentOwnerPID;
} mutexType;

void mutexLock(mutex_t mutexID);
void mutexUnlock(mutex_t mutexID);
void mutexCreate(mutex_t mutexID);
void mutexDelete(mutex_t mutexID);
