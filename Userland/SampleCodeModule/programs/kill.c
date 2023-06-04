#include <userlandApps.h>
// #include <userStdF.h>

int kill(char ** args){
    int pid = atoi(args[0]);
    if (pid > 0){
        if(killProcess(pid) == 0){
            printf(BLUE, "Proceso %d eliminado\n", pid);
        }
        else {
            printf(RED, "No existe el proceso %d\n", pid);
        }
        printf(BLUE, "VOLVI\n");
    }

    return 0;
}