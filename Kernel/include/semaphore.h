
// Se abre y me uno con el nombre
// cuando se abre un semaphore se agrega a la primer posicion del vector libre
// para post y wait lo haces con el id (donde esta ubicado el sem en el vector)

#include <queueADT.h>
#include <lib.h>

typedef int sem_t;

#define SEM_MAX 100

sem_t semCreate(char *name, int initValue); // Adds a new semaphore to the array
sem_t semOpen(char *name);                  // Opens an existing semaphore
int semClose(sem_t semId);                  // Closes the semaphore. returns 0 if success, -1 if error
int semDestroy(sem_t semId);                // Destroys the semaphore. returns 0 if success, -1 if error
int semWait(sem_t semId);                   // Decrements semaphore, or blocks process if semaphore is 0
int semPost(sem_t semId);                   // Increments semaphore

typedef struct
{
    char *name;
    Queue *blockedProcesses;
    size_t value;
} semaphoreType;
