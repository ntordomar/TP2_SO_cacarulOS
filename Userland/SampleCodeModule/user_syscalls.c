#include <user_syscalls.h>
#include <userLib.h>

void sys_read( char * buff, int length){
    sys_int_80(2,buff,length, 0, 0, 0);
}

void sys_write(int x, int y, char * c) {
    sys_int_80(1, x, y, c, 0, 0);
}

void sys_draw_rectangle(int x, int y, int width, int height, int color) {
    sys_int_80(3, x, y, width, height, color);
}

void sys_clear_screen() {
    sys_int_80(4, 0, 0, 0, 0, 0);
}
