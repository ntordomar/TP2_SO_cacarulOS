#include <stdint.h>

void sys_call_handler(uint64_t mode, uint64_t r1, uint64_t r2, uint64_t r3, uint64_t r4,uint64_t r5 );

void _0_empty(uint64_t r1, uint64_t r2, uint64_t r3, uint64_t r4,uint64_t r5);

void _1_write(uint64_t x, uint64_t y, uint64_t c, uint64_t len, uint64_t fd);

void _2_read(uint64_t buffer, uint64_t length);

void _3_draw_rectangle (uint64_t x, uint64_t y, uint64_t w, uint64_t h, uint64_t color);

void _4_clear_screen();

void _5_write_char(uint64_t x, uint64_t y, uint64_t c, uint64_t fd);

void _6_get_seconds(uint64_t sec);

void _7_get_minutes(uint64_t min);

void _8_get_hours(uint64_t hour);

void _9_set_font_size(uint64_t size);

void _10_capture_registers();