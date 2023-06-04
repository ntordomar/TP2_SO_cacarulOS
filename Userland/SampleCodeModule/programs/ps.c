#include "../include/userlandApps.h"

int ps(char **args)
{
    processInfo *p;
    int *pids = getProcesses();
    // recorro el arreglo de pids y voy imprimiendo la informacion de los procesos
    char *status = malloc(10);
    printf(GREEN, "\n");
    printf(GREEN, "PID | Name | Parent |   RSP   |   RBP   | Priority | Foreground | State\n");
    printf(GREEN, "------------------------------------------------------------------------\n");
    for (int i = 0; pids[i] != -1; i++)
    {
        p = getProcessInfo(pids[i]);
        status = strcpy(status, p->state == 0 ? "READY" : (p->state == 1 ? "RUNNING" : (p->state == 2 ? "BLOCKED" : (p->state == 3 ? "ZOMBIE" : "DEAD"))));
        printf(WHITE, "%d  | %s | %d | %x | %x | %d | %s | %s\n", p->pid, p->name, p->parent, p->rsp, p->rbp, p->priority, p->foreground ? "TRUE" : "FALSE", status);
    }
    printf(GREEN, "------------------------------------------------------------------------\n");
    free(pids);
    free(status);
    return 0;
}