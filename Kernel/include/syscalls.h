#include <stdint.h>

void sys_call_handler(uint64_t mode, uint64_t r1, uint64_t r2, uint64_t r3, uint64_t r4,uint64_t r5 );

void _0_empty(uint64_t r1, uint64_t r2, uint64_t r3, uint64_t r4,uint64_t r5);

void _1_writeChar(uint64_t x, uint64_t y, uint64_t c);

void _2_read(uint64_t buffer, uint64_t length);

void _3_draw_rectangle (uint64_t x, uint64_t y, uint64_t w, uint64_t h, uint64_t color);

void _4_clear_screen();