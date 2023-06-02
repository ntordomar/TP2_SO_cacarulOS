#include <stdint.h>
uint64_t sys_read(char * buff, int length);
uint64_t sys_write(int x, int y, char*  c, int len, int color);
uint64_t sys_draw_rectangle(int x, int y, int width, int height, int color);
uint64_t sys_clear_screen();
uint64_t sys_write_char(int x, int y, char c, int color);
uint64_t sys_get_seconds(int * sec);
uint64_t sys_get_minutes(int * min);
uint64_t sys_get_hours(int * hours);
uint64_t sys_change_font_size(int size);
uint64_t sys_get_ticks(int ticks);
uint64_t sys_beep(int freq, int time);
uint64_t sys_get_mem(int memoryPos, unsigned char * buff);
uint64_t sys_get_regs(int * captured, int * regs);

// NEW SYSCALLS

uint64_t sys_create_process(char * name, char ** args, char * code, int foreground);
uint64_t sys_malloc(int size, void * ptr);
uint64_t sys_free(void * ptr);
uint64_t sys_get_pid();
uint64_t sys_kill(int pid);
uint64_t sys_exit();
uint64_t sys_nice(int pid, int priority);
uint64_t sys_block(int pid);
uint64_t sys_resume(int pid);
uint64_t sys_heap_info();
uint64_t sys_process_info(int pid);
uint64_t sys_waitpid(int pid);
uint64_t sys_sem_open(char * name);
uint64_t sys_sem_close(int semId);
uint64_t sys_sem_destroy(int semId);
uint64_t sys_pipe_open(char * name);
uint64_t sys_pipe_destroy(int name);
uint64_t sys_sem_print(int semId);
uint64_t sys_sem_create(char * name, int initValue);
uint64_t sys_sem_wait(int semId);
uint64_t sys_sem_post(int semId);
uint64_t sys_pipe_create(char * name);
uint64_t sys_pipe_create_anonymus();
