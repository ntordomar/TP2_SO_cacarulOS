#include <semaphore.h>

semaphoreType semaphores[SEM_MAX];

void semInit()
{
    int i;
    // Initialize all semaphores to NULL
    for (i = 0; i < SEM_MAX; i++)
    {
        semaphores[i].name = NULL;
    }
}

sem_t semCreate(char *name, int initValue)
{
    int i = 0;
    // Find first free position in the array
    while (i < SEM_MAX && semaphores[i].name != NULL)
    {
        i++;
    }
    if (i == SEM_MAX)
    {
        // No free positions
        return -1;
    }
    // Create semaphore
    semaphores[i].name = malloc(strlen(name) + 1); // +1 for '\0' character
    strcpy(semaphores[i].name, name);
    semaphores[i].value = initValue;
    semaphores[i].blockedProcesses = createQueue();
    return i;
}

sem_t semOpen(char *name) {
    int i = 0;
    // Find semaphore with given name
    while (i < SEM_MAX && (semaphores[i].name == NULL || strcmp(semaphores[i].name, name) != 0))
    {
        i++;
    }
    if (i == SEM_MAX)
    {
        // No semaphore with given name
        return -1;
    }
    return i;
}