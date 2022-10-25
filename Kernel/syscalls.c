#include <syscalls.h>
#include <stdint.h>
#include <video.h>
#include <keyBoardHandler.h>
#include <lib.h>
#include <time.h>
// #include <interrupts.h>

static void (*sysFunctions[20])(uint64_t r1, uint64_t r2, uint64_t r3, uint64_t r4,uint64_t r5) = {_0_empty,
_1_write,_2_read,_3_draw_rectangle,_4_clear_screen, _5_write_char, _6_get_seconds, _7_get_minutes, _8_get_hours,
_9_set_font_size, _10_capture_registers, _11_get_ticks};

void sys_call_handler(uint64_t mode, uint64_t r1, uint64_t r2, uint64_t r3, uint64_t r4,uint64_t r5 ){ // pasamos todos ints, en el caso en el que sea un numero, se lee como un numero, en el caso de que esa una direccion de memoria, se castea a la que se necesita :)
    (*sysFunctions[mode])(r1,r2,r3,r4,r5);
    _sti();
	return;
}

void _0_empty(uint64_t r1, uint64_t r2, uint64_t r3, uint64_t r4,uint64_t r5){
    ;
} 

void _1_write(uint64_t x, uint64_t y, uint64_t c, uint64_t len, uint64_t color){
    draw_string(x, y, (char *) c, len, color, BLACK);
} 


void _2_read(uint64_t buffer, uint64_t length){
    ((char*) buffer)[0] = nextElement();
    // for(int i = 0; i< length; i++){
    //     char c;
    //     if((c = nextElement()) == -1) return;
    //     ((char *)buffer)[i] = c;
    // }

} 


void _3_draw_rectangle (uint64_t x, uint64_t y, uint64_t w, uint64_t h, uint64_t color) {
    fillrect(x, y, color, w, h);    
}

void _4_clear_screen(){
    clearScreen();

}

void _5_write_char(uint64_t x, uint64_t y, uint64_t c, uint64_t color) {
    draw_char(x, y, c, color, BLACK);
}

void _6_get_seconds(uint64_t sec) {
    *((int *)sec) = getSeconds();
}

void _7_get_minutes(uint64_t min) {
    *((int *)min) = getMinutes();
}

void _8_get_hours(uint64_t hour) {
    *((int *)hour) = getHours();

}

void _9_set_font_size(uint64_t size) {
    set_default_fontSize(size);
}

void _10_capture_registers() {

}

void _11_get_ticks(uint64_t  ticks) {
    *((int *)ticks) = ticks_elapsed();
}