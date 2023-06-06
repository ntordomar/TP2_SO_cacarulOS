// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdint.h>
#include "user_syscalls.h"
#include "test_util.h"
#include <userStdF.h>

#define MINOR_WAIT "1000000" // TODO: Change this value to prevent a process from flooding the screen
#define WAIT 100000000       // TODO: Change this value to make the wait long enough to see theese processes beeing run at least twice

#define TOTAL_PROCESSES 3
#define LOWEST 1  // TODO: Change as required
#define MEDIUM 3  // TODO: Change as required
#define HIGHEST 5 // TODO: Change as required

int64_t prio[TOTAL_PROCESSES] = {LOWEST, MEDIUM, HIGHEST};

int test_prio(char **args)
{
  int64_t pids[TOTAL_PROCESSES];
  char *argv[] = {MINOR_WAIT, NULL};
  uint64_t i;
  int fds[2] = {0, 0};
  for (i = 0; i < TOTAL_PROCESSES; i++)
    pids[i] = sys_create_process("endless_loop_print", argv, &endless_loop_print, 0, fds);

  bussy_wait(WAIT);
  printf(WHITE, "\nCHANGING PRIORITIES...\n");

  for (i = 0; i < TOTAL_PROCESSES; i++)
    sys_nice(pids[i], prio[i]);

  bussy_wait(WAIT);
  printf(WHITE, "\nBLOCKING...\n");

  for (i = 0; i < TOTAL_PROCESSES; i++)
    sys_block(pids[i]);

  printf(WHITE, "CHANGING PRIORITIES WHILE BLOCKED...\n");

  for (i = 0; i < TOTAL_PROCESSES; i++)
    sys_nice(pids[i], MEDIUM);

  printf(WHITE, "UNBLOCKING...\n");

  for (i = 0; i < TOTAL_PROCESSES; i++)
    sys_resume(pids[i]);

  bussy_wait(WAIT);
  printf(WHITE, "\nKILLING...\n");

  for (i = 0; i < TOTAL_PROCESSES; i++)
    killProcess(pids[i]);
  for (i = 0; i < TOTAL_PROCESSES; i++)
    sys_waitpid(pids[i]);

  return 0;
}