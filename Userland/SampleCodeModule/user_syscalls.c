#include <user_syscalls.h>
#include <userLib.h>

void sys_read( char * buff, int length){
    sys_int_80(2,buff,length, 0, 0, 0);
} 

void sys_write(int x, int y, char * c, int len, int color) {
    sys_int_80(1, x, y, c, len, color);
}

void sys_draw_rectangle(int x, int y, int width, int height, int color) {
    sys_int_80(3, x, y, width, height, color);
}

void sys_clear_screen() {
    sys_int_80(4, 0, 0, 0, 0, 0);
}
void sys_write_char(int x, int y, char c, int color){
    sys_int_80(5,x,y,c,color,0);
}


//segundos de la hora
void sys_get_seconds(int * sec){
    sys_int_80(6, sec, 0, 0, 0,0);
}
void sys_get_minutes(int * min ){
    sys_int_80(7, min, 0, 0, 0, 0);
}
void sys_get_hours(int * hours){
    sys_int_80(8, hours, 0, 0, 0, 0);
}

void sys_change_font_size(int size) {
    sys_int_80(9, size, 0, 0, 0, 0);
}

void sys_capture_registers() {
    sys_int_80(10, 0, 0, 0, 0, 0);
}

void sys_get_ticks(int * ticks) {
    sys_int_80(11, ticks, 0, 0, 0, 0);
}