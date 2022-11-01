#include <user_syscalls.h>
#include <userLib.h>

void sys_read( char * buff, int length){
    sys_int_80((uint64_t)2,(uint64_t)buff,(uint64_t)length, 0, 0, 0);
} 

void sys_write(int x, int y, char * c, int len, int color) {
    sys_int_80((uint64_t)1,(uint64_t) x,(uint64_t) y,(uint64_t) c,(uint64_t) len, (uint64_t)color);
}

void sys_draw_rectangle(int x, int y, int width, int height, int color) {
    sys_int_80((uint64_t)3,(uint64_t) x,(uint64_t) y,(uint64_t) width,(uint64_t) height, (uint64_t)color);
}

void sys_clear_screen() {
    sys_int_80((uint64_t)4, 0, 0, 0, 0, 0);
}
void sys_write_char(int x, int y, char c, int color){
    sys_int_80((uint64_t)5,(uint64_t)x,(uint64_t)y,(uint64_t)c,(uint64_t)color,0);
}



void sys_get_seconds(int * sec){
    sys_int_80((uint64_t)6, (uint64_t)sec, 0, 0, 0,0);
}
void sys_get_minutes(int * min ){
    sys_int_80((uint64_t)7, (uint64_t)min, 0, 0, 0, 0);
}
void sys_get_hours(int * hours){
    sys_int_80((uint64_t)8, (uint64_t)hours, 0, 0, 0, 0);
}

void sys_change_font_size(int size) {
    sys_int_80((uint64_t)9, (uint64_t)size, 0, 0, 0, 0);
}

void sys_beep(int freq, int time){
    sys_int_80((uint64_t)10,(uint64_t)freq,(uint64_t)time,0,0,0);
}

void sys_get_ticks(int ticks) {
    sys_int_80((uint64_t)11, (uint64_t)ticks, 0, 0, 0, 0);
}

