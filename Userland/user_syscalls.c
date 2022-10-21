#include <user_syscalls.h>

extern void sys_int_80(int mode, int r1, int r2, int r3, int r4, int r5);

void sys_read( char * buff, int length){
    sys_int_80(1,buff,length, 0, 0, 0);
}

void sys_write(int x, int y, int c) {
    sys_int_80(2, x, y, c, 0, 0);
}

void sys_draw_rectangle(int x, int y, int width, int height, int color) {
    sys_int_80(3, x, y, width, height, color);
}

void sys_clear_screen() {
    sys_int_80(4, 0, 0, 0, 0, 0);
}
