#include <user_syscalls.h>
#include <userStdF.h>
unsigned int getc(){
    char c;
    sys_read(&c, 1);
    if (c == 0){
        return -1; // EOF
    }
    return (unsigned int)c;
}