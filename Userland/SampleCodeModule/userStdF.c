#include <user_syscalls.h>
#include <userStdF.h>
char getc(){
    char buff[2];
    int len = 2;
    sys_read(&buff, len);
    // char c;
    // sys_read(&c, 1);
    // if (c == 0){
    //     return -1; // EOF
    // }
    // return (unsigned int)c;
    // for (int i = 0; i<4; i++){
    //     sys_write_char(200 + 4*i, 200, buff[i], 1);
    // }
    return buff[0];
}