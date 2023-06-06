#include <user_syscalls.h>
#include <userLib.h>

uint64_t sys_read(char *buff, int length)
{
    return sys_int_80((uint64_t)2, (uint64_t)buff, (uint64_t)length, 0, 0, 0);
}

uint64_t sys_write(int x, int y, char *c, int len, int color)
{
    return sys_int_80((uint64_t)1, (uint64_t)x, (uint64_t)y, (uint64_t)c, (uint64_t)len, (uint64_t)color);
}

uint64_t sys_draw_rectangle(int x, int y, int width, int height, int color)
{
    return sys_int_80((uint64_t)3, (uint64_t)x, (uint64_t)y, (uint64_t)width, (uint64_t)height, (uint64_t)color);
}

uint64_t sys_clear_screen()
{
    return sys_int_80((uint64_t)4, 0, 0, 0, 0, 0);
}
uint64_t sys_write_char(int x, int y, char c, int color)
{
    return sys_int_80((uint64_t)5, (uint64_t)x, (uint64_t)y, (uint64_t)c, (uint64_t)color, 0);
}

uint64_t sys_get_seconds(int *sec)
{
    return sys_int_80((uint64_t)6, (uint64_t)sec, 0, 0, 0, 0);
}
uint64_t sys_get_minutes(int *min)
{
    return sys_int_80((uint64_t)7, (uint64_t)min, 0, 0, 0, 0);
}
uint64_t sys_get_hours(int *hours)
{
    return sys_int_80((uint64_t)8, (uint64_t)hours, 0, 0, 0, 0);
}

uint64_t sys_change_font_size(int size)
{
    return sys_int_80((uint64_t)9, (uint64_t)size, 0, 0, 0, 0);
}

uint64_t sys_beep(int freq, int time)
{
    return sys_int_80((uint64_t)10, (uint64_t)freq, (uint64_t)time, 0, 0, 0);
}

uint64_t sys_get_ticks(int ticks)
{
    return sys_int_80((uint64_t)11, (uint64_t)ticks, 0, 0, 0, 0);
}

uint64_t sys_get_mem(int memoryPos, unsigned char *buff)
{
    return sys_int_80((uint64_t)12, (uint64_t)memoryPos, (uint64_t)buff, 0, 0, 0);
}

uint64_t sys_get_regs(int *captured, int *regs)
{
    return sys_int_80((uint64_t)13, (uint64_t)captured, (uint64_t)regs, 0, 0, 0);
}

/* --- NEW SYSCALLS --- */

uint64_t sys_create_process(char *name, char **args, char *code, int foreground, int *fds)
{
    return sys_int_80((uint64_t)14, (uint64_t)name, (uint64_t)args, (uint64_t)code, (uint64_t)foreground, (uint64_t)fds);
}

uint64_t sys_malloc(int size, void *ptr)
{
    return sys_int_80((uint64_t)15, (uint64_t)size, (uint64_t)ptr, 0, 0, 0);
}

uint64_t sys_free(void *ptr)
{
    return sys_int_80((uint64_t)16, (uint64_t)ptr, 0, 0, 0, 0);
}

uint64_t sys_get_pid()
{
    return sys_int_80((uint64_t)17, 0, 0, 0, 0, 0);
}

uint64_t sys_kill(int pid)
{
    return sys_int_80((uint64_t)18, (uint64_t)pid, 0, 0, 0, 0);
}

uint64_t sys_exit()
{
    return sys_int_80((uint64_t)19, 0, 0, 0, 0, 0);
}

uint64_t sys_nice(int pid, int priority)
{
    return sys_int_80((uint64_t)20, (uint64_t)pid, (uint64_t)priority, 0, 0, 0);
}

uint64_t sys_block(int pid)
{
    return sys_int_80((uint64_t)21, (uint64_t)pid, 0, 0, 0, 0);
}

uint64_t sys_resume(int pid)
{
    return sys_int_80((uint64_t)22, (uint64_t)pid, 0, 0, 0, 0);
}

uint64_t sys_heap_info()
{
    return sys_int_80((uint64_t)23, 0, 0, 0, 0, 0);
}

uint64_t sys_process_info(int pid)
{
    return sys_int_80((uint64_t)24, pid, 0, 0, 0, 0);
}

uint64_t sys_waitpid(int pid)
{
    return sys_int_80((uint64_t)25, pid, 0, 0, 0, 0);
}

uint64_t sys_sem_open(char *name)
{
    return sys_int_80((uint64_t)26, (uint64_t)name, 0, 0, 0, 0);
}

uint64_t sys_sem_close(int semId)
{
    return sys_int_80((uint64_t)27, (uint64_t)semId, 0, 0, 0, 0);
}

uint64_t sys_sem_destroy(int semId)
{
    return sys_int_80((uint64_t)28, (uint64_t)semId, 0, 0, 0, 0);
}

uint64_t sys_pipe_open(char *name)
{
    return sys_int_80((uint64_t)29, (uint64_t)name, 0, 0, 0, 0);
}

uint64_t sys_pipe_destroy(int name)
{
    return sys_int_80((uint64_t)30, (uint64_t)name, 0, 0, 0, 0);
}

uint64_t sys_sem_print(int semId)
{
    return sys_int_80((uint64_t)31, (uint64_t)semId, 0, 0, 0, 0);
}

uint64_t sys_sem_create(char *name, int initValue)
{
    return sys_int_80((uint64_t)32, (uint64_t)name, (uint64_t)initValue, 0, 0, 0);
}

uint64_t sys_sem_wait(int semId)
{
    return sys_int_80((uint64_t)33, (uint64_t)semId, 0, 0, 0, 0);
}

uint64_t sys_sem_post(int semId)
{
    return sys_int_80((uint64_t)34, (uint64_t)semId, 0, 0, 0, 0);
}

uint64_t sys_pipe_create(char *name)
{
    return sys_int_80((uint64_t)35, (uint64_t)name, 0, 0, 0, 0);
}

uint64_t sys_pipe_create_anonymous()
{
    return sys_int_80((uint64_t)36, 0, 0, 0, 0, 0);
}

uint64_t sys_pids_array()
{
    return sys_int_80((uint64_t)37, 0, 0, 0, 0, 0);
}

uint64_t sys_get_current_stdout()
{
    return sys_int_80((uint64_t)38, 0, 0, 0, 0, 0);
}

uint64_t sys_sem_create_anonymous(int initValue)
{
    return sys_int_80((uint64_t)39, (uint64_t)initValue, 0, 0, 0, 0);
}

uint64_t sys_yield() {
    return sys_int_80((uint64_t)40, 0, 0, 0, 0, 0);
}
