#include <userlandApps.h>

int nice(char ** args){
    return setNiceness(args[0], args[1]);
}