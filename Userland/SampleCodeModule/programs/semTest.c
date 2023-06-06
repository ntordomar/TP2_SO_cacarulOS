// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdint.h>
#include "user_syscalls.h"
#include "test_util.h"
#include "userStdF.h"
#include <user_syscalls.h>

#define SEM_ID "sem"
#define TOTAL_PAIR_PROCESSES 2

int64_t global; // shared memory
int semId;
void slowInc(int64_t *p, int64_t inc)
{
  uint64_t aux = *p;
  aux += inc;
  for (int i = 0; i < 30000; i++)
  {
    for (int j = 0; j < 1500; j++)
      ;
  }
  *p = aux;
}

int my_process_inc(char **args)
{
  uint64_t n;
  int8_t inc;
  int8_t use_sem;

  if (args[3] != NULL)
  {
    return -1;
  }

  if ((n = satoi(args[0])) <= 0)
    return -1;
  if ((inc = satoi(args[1])) == 0)
    return -1;
  if ((use_sem = satoi(args[2])) < 0)
    return -1;

  if (use_sem)
  {
    if (!sys_sem_open(SEM_ID))
    {
      printf(WHITE, "test_sync: ERROR opening semaphore\n");
      return -1;
    }
  }

  uint64_t i;
  for (i = 0; i < n; i++)
  {
    if (use_sem)
      semWait(semId);
    slowInc(&global, inc);
    if (use_sem)
    {
      semPost(semId);
    }
  }

  if (use_sem)
  {
    semClose(semId);
  }
  return 0;
}

int test_sync(char **args)
{ //{n, use_sem, 0}
  uint64_t pids[2 * TOTAL_PAIR_PROCESSES];

  if (args[2] != NULL)
    return -1;

  char *argvDec[] = {args[0], "-1", args[1], NULL};
  char *argvInc[] = {args[0], "1", args[1], NULL};

  global = 0;

  uint64_t i;
  semId = semCreate(SEM_ID, 1);

  for (i = 0; i < TOTAL_PAIR_PROCESSES; i++)
  {
    int fds[3] = {0, 0, 0};
    int fds2[3] = {0, 0, 0};
    pids[i] = sys_create_process("my_process_inc", argvDec, &my_process_inc, 0, fds);
    pids[i + TOTAL_PAIR_PROCESSES] = sys_create_process("my_process_inc", argvInc, &my_process_inc, 0, fds2);
  }
  for (i = 0; i < TOTAL_PAIR_PROCESSES; i++)
  {
    sys_waitpid(pids[i]);
    sys_waitpid(pids[i + TOTAL_PAIR_PROCESSES]);
  }
  semDestroy(semId);

  printf(WHITE, "Final value: %d\n", global);

  return 0;
}