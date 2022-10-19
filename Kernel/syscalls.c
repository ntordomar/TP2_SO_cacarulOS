#include <syscalls.h>
#include <naiveConsole.h>

void sys_write_handler(int fd, char * buff, int bytes){
    switch (fd)
    {
    case 1:
        ncPrintBytes(buff, bytes, 0x0F);
        break;

    case 2:
        ncPrintBytes(buff, bytes, 0x04);
        break;
    default:
        break;
    }
}