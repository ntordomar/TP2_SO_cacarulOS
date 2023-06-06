#include <stdint.h>

uint64_t sys_call_handler(uint64_t mode, uint64_t r1, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5);

uint64_t _0_empty(uint64_t r1, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5);

uint64_t _1_write(uint64_t x, uint64_t y, uint64_t c, uint64_t len, uint64_t fd);

uint64_t _2_read(uint64_t buffer, uint64_t length, uint64_t r3, uint64_t r4, uint64_t r5);

uint64_t _3_draw_rectangle(uint64_t x, uint64_t y, uint64_t w, uint64_t h, uint64_t color);

uint64_t _4_clear_screen(uint64_t r1, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5);

uint64_t _5_write_char(uint64_t x, uint64_t y, uint64_t c, uint64_t fd, uint64_t r5);

uint64_t _6_get_seconds(uint64_t sec, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5);

uint64_t _7_get_minutes(uint64_t min, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5);

uint64_t _8_get_hours(uint64_t hour, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5);

uint64_t _9_set_font_size(uint64_t size, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5);

uint64_t _10_beep(uint64_t frequency, uint64_t time, uint64_t r3, uint64_t r4, uint64_t r5);

uint64_t _11_get_ticks(uint64_t ticks, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5);

uint64_t _12_get_mem(uint64_t memoryPos, uint64_t buff, uint64_t r3, uint64_t r4, uint64_t r5);

uint64_t _13_get_regs(uint64_t wasCaptured, uint64_t registers, uint64_t r3, uint64_t r4, uint64_t r5);

uint64_t _14_create_process(uint64_t name, uint64_t args, uint64_t code, uint64_t foreground, uint64_t fds);

uint64_t _15_malloc(uint64_t size, uint64_t ptr, uint64_t r3, uint64_t r4, uint64_t r5);

uint64_t _16_free(uint64_t ptr, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5);

uint64_t _17_getpid(uint64_t pid, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5);

uint64_t _18_kill(uint64_t pid, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5);

uint64_t _19_exit(uint64_t r1, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5);

uint64_t _20_nice(uint64_t pid, uint64_t priority, uint64_t r3, uint64_t r4, uint64_t r5);

uint64_t _21_block(uint64_t pid, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5);

uint64_t _22_resume(uint64_t pid, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5);

uint64_t _23_heap_info();

uint64_t _24_get_proc_info(uint64_t pid, uint64_t info, uint64_t r3, uint64_t r4, uint64_t r5);

uint64_t _25_waitpid(uint64_t pid, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5);

uint64_t _26_sem_open(uint64_t name, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5);

uint64_t _27_sem_close(uint64_t semID, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5);

uint64_t _28_sem_destroy(uint64_t semID, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5);

uint64_t _29_pipe_open(uint64_t name, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5);

uint64_t _30_pipe_destroy(uint64_t name, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5);

uint64_t _31_sem_print(uint64_t semId, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5);

uint64_t _32_sem_create(uint64_t name, uint64_t initValue, uint64_t r3, uint64_t r4, uint64_t r5);

uint64_t _33_sem_wait(uint64_t semId, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5);

uint64_t _34_sem_post(uint64_t semId, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5);

uint64_t _35_pipe_create(uint64_t name, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5);

uint64_t _36_pipe_create_anonymous(uint64_t r1, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5);

uint64_t _37_pids_array(uint64_t r1, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5);

uint64_t _38_get_current_stdout(uint64_t r1, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5);

uint64_t _39_sem_create_anonymous(uint64_t initValue, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5);

uint64_t _40_yield (uint64_t r1, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5);