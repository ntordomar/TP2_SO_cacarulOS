#include <stdint.h>

void sys_call_handler(uint64_t mode, uint64_t r1, uint64_t r2, uint64_t r3, uint64_t r4,uint64_t r5 );

void _0_empty(uint64_t r1, uint64_t r2, uint64_t r3, uint64_t r4,uint64_t r5);

void _1_write(uint64_t x, uint64_t y, uint64_t c, uint64_t len, uint64_t fd);

void _2_read(uint64_t buffer, uint64_t length, uint64_t r3, uint64_t r4, uint64_t r5);

void _3_draw_rectangle (uint64_t x, uint64_t y, uint64_t w, uint64_t h, uint64_t color);

void _4_clear_screen(uint64_t r1, uint64_t r2, uint64_t r3, uint64_t r4,uint64_t r5);

void _5_write_char(uint64_t x, uint64_t y, uint64_t c, uint64_t fd, uint64_t r5);

void _6_get_seconds(uint64_t sec, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5);

void _7_get_minutes(uint64_t min, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5);

void _8_get_hours(uint64_t hour, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5);

void _9_set_font_size(uint64_t size, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5);

void _10_beep(uint64_t frequency, uint64_t time, uint64_t r3, uint64_t r4, uint64_t r5);

void _11_get_ticks(uint64_t ticks, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5);

void _12_get_mem(uint64_t memoryPos, uint64_t buff);

void _13_get_regs(uint64_t wasCaptured, uint64_t registers );