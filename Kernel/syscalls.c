#include <syscalls.h>
#include <video.h>
#include <keyBoardHandler.h>
#include <lib.h>
#include <time.h>
#include <speaker.h>
#include <pipe.h>
// #include <heap.h>
#include <sync.h>

extern uint8_t capturedReg;
extern const uint64_t registers[17];

static uint64_t (*sysFunctions[])(uint64_t r1, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5) = {_0_empty,
    _1_write, _2_read, _3_draw_rectangle, _4_clear_screen, _5_write_char, _6_get_seconds, _7_get_minutes, _8_get_hours,
    _9_set_font_size, _10_beep, _11_get_ticks, _12_get_mem, _13_get_regs, _14_create_process, _15_malloc, _16_free, _17_getpid,
    _18_kill, _19_exit, _20_nice, _21_block, _22_resume, _23_heap_info, _24_get_proc_info, _25_waitpid, _26_sem_open, _27_sem_close,
    _28_sem_destroy, _29_pipe_open, _30_pipe_destroy, _31_sem_print, _32_sem_create, _33_sem_wait, _34_sem_post, _35_pipe_create,
    _36_pipe_create_anonymous, _37_pids_array};

uint64_t sys_call_handler(uint64_t mode, uint64_t r1, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5)
{ // pasamos todos ints, en el caso en el que sea un numero, se lee como un numero, en el caso de que esa una direccion de memoria, se castea a la que se necesita :)
    return (*sysFunctions[mode])(r1, r2, r3, r4, r5);
}

uint64_t _0_empty(uint64_t r1, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5)
{
    return 0;
}

uint64_t _1_write(uint64_t x, uint64_t y, uint64_t c, uint64_t len, uint64_t color)
{
    PCB *currentProcessPCB = getCurrentPCB();
    if (currentProcessPCB->process->fd[FD_WRITE] == SHELL)
    {
        if (currentProcessPCB->process->foreground)
        {
            draw_string(x, y, (char *)c, len, color, BLACK);
        }
    }
    else
    {
        return pipeWrite(currentProcessPCB->process->fd[FD_WRITE], (char *)c, len);
    }
    return 0;
}

uint64_t _2_read(uint64_t buffer, uint64_t length, uint64_t r3, uint64_t r4, uint64_t r5)
{
    PCB *currentProcessPCB = getCurrentPCB();
    if (currentProcessPCB->process->fd[FD_READ] == SHELL)
    {
        if (currentProcessPCB->process->foreground)
        {
            ((char *)buffer)[0] = nextElement();
        }
        else
        {
            blockProcess(currentProcessPCB->process->pid);
        }
    }
    else
    {
        return pipeRead(currentProcessPCB->process->fd[FD_READ], (char *)buffer, length);
    }
    return 0;
}

uint64_t _3_draw_rectangle(uint64_t x, uint64_t y, uint64_t w, uint64_t h, uint64_t color)
{
    fillrect(x, y, color, w, h);
    return 0;
}

uint64_t _4_clear_screen(uint64_t r1, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5)
{
    clearScreen();
    return 0;
}

uint64_t _5_write_char(uint64_t x, uint64_t y, uint64_t c, uint64_t color, uint64_t r5)
{
    draw_char(x, y, c, color, BLACK);
    return 0;
}

uint64_t _6_get_seconds(uint64_t sec, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5)
{
    *((int *)sec) = getSeconds();
    return sec;
}

uint64_t _7_get_minutes(uint64_t min, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5)
{
    *((int *)min) = getMinutes();
    return min;
}

uint64_t _8_get_hours(uint64_t hour, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5)
{
    *((int *)hour) = getHours();
    return hour;
}

uint64_t _9_set_font_size(uint64_t size, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5)
{
    set_default_fontSize(size);
    return 0;
}

uint64_t _10_beep(uint64_t frequency, uint64_t time, uint64_t r3, uint64_t r4, uint64_t r5)
{
    beep((int)frequency, (int)time);
    return 0;
}

uint64_t _11_get_ticks(uint64_t delta, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5)
{
    hold((int)delta);
    return 0;
}

uint64_t _12_get_mem(uint64_t memoryPos, uint64_t buff, uint64_t r3, uint64_t r4, uint64_t r5)
{
    getMemory((int)memoryPos, (unsigned char *)buff);
    return 0;
}

uint64_t _13_get_regs(uint64_t wasCaptured, uint64_t regs, uint64_t r3, uint64_t r4, uint64_t r5)
{
    *((int *)wasCaptured) = capturedReg;
    if (wasCaptured)
    {
        for (int i = 0; i < 17; i++)
        {
            ((int *)regs)[i] = registers[i];
        }
    }
    return 0;
}

/* --- NEW SYSCALLS --- */

uint64_t _14_create_process(uint64_t name, uint64_t args, uint64_t code, uint64_t foreground, uint64_t r5)
{
    return createProcess((char *)name, -1, 4096, 4096, (char **)args, (void *)code, (char)foreground);
}

uint64_t _15_malloc(uint64_t size, uint64_t ptr, uint64_t r3, uint64_t r4, uint64_t r5)
{
    ptr = malloc(size);
    return ptr;
}

uint64_t _16_free(uint64_t ptr, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5)
{
    free((void *)ptr);
    return 0;
}

uint64_t _17_getpid(uint64_t r1, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5)
{
    return getCurrentPCB()->process->pid;
}

uint64_t _18_kill(uint64_t pid, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5)
{
    return killProcess((int)pid);
}

uint64_t _19_exit(uint64_t r1, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5)
{
    return killProcess((int)getCurrentPid());
}

uint64_t _20_nice(uint64_t pid, uint64_t priority, uint64_t r3, uint64_t r4, uint64_t r5)
{
    changePriority(pid, priority);
    return 0;
}

uint64_t _21_block(uint64_t pid, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5)
{
    return blockProcess(pid);
}

uint64_t _22_resume(uint64_t pid, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5)
{
    return unblockProcess(pid);
}

uint64_t _23_heap_info(uint64_t r1, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5)
{
    return (uint64_t)getHeapInfo();
}

uint64_t _24_get_proc_info(uint64_t pid, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5)
{
    return getProcessInfo(pid);
}

uint64_t _25_waitpid(uint64_t pid, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5)
{
    return waitpid((int)pid);
}

uint64_t _26_sem_open(uint64_t name, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5)
{
    return semOpen((char *)name);
}

uint64_t _27_sem_close(uint64_t semID, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5)
{
    return semClose((sem_t)semID);
}

uint64_t _28_sem_destroy(uint64_t semID, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5)
{
    return semDestroy((sem_t)semID);
}

uint64_t _29_pipe_open(uint64_t name, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5)
{
    return getPipeIdByName((int)name);
}

uint64_t _30_pipe_destroy(uint64_t name, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5)
{
    pipeDestroy((int)name);
    return 0;
}

uint64_t _31_sem_print(uint64_t semId, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5)
{
    return semPrint((int)semId);
}

uint64_t _32_sem_create(uint64_t name, uint64_t initValue, uint64_t r3, uint64_t r4, uint64_t r5)
{
    return semCreate((char *)name, (int)initValue);
}

uint64_t _33_sem_wait(uint64_t semId, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5)
{
    return semWait((int)semId);
}

uint64_t _34_sem_post(uint64_t semId, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5)
{
    return semPost((int)semId);
}

uint64_t _35_pipe_create(uint64_t name, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5)
{
    return pipeCreateWithName((char *)name);
}

uint64_t _36_pipe_create_anonymous(uint64_t r1, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5)
{
    return pipeCreateAnonymous();
}

uint64_t _37_pids_array(uint64_t r1, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5)
{
    return getPidsArray();
}