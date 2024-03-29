// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "user_syscalls.h"
#include "test_util.h"
#include <userlandApps.h>

#define MAX_BLOCKS 128

typedef struct MM_rq
{
  void *address;
  uint32_t size;
} mm_rq;

void *my_memset(void *destination, int32_t c, uint64_t length)
{
  uint8_t chr = (uint8_t)c;
  char *dst = (char *)destination;
  while (length--)
  {
    dst[length] = chr;
  }
  return destination;
}

int test_mem(char **args)
{
  mm_rq mm_rqs[MAX_BLOCKS];
  uint8_t rq;
  uint32_t total;
  uint64_t max_memory;

  if (args[1] != NULL)
    return -1;

  if ((max_memory = satoi(args[0])) <= 0)
    return -1;

  while (1)
  {
    rq = 0;
    total = 0;

    // Request as many blocks as we can
    while (rq < MAX_BLOCKS && total < max_memory)
    {
      mm_rqs[rq].size = GetUniform(max_memory - total - 1) + 1;
      mm_rqs[rq].address = malloc(mm_rqs[rq].size);

      if (mm_rqs[rq].address)
      {
        total += mm_rqs[rq].size;
        rq++;
      }
    }

    // Set
    uint32_t i;
    for (i = 0; i < rq; i++)
      if (mm_rqs[i].address)
        my_memset(mm_rqs[i].address, i, mm_rqs[i].size);

    // Check
    for (i = 0; i < rq; i++)
      if (mm_rqs[i].address)
        if (!memcheck(mm_rqs[i].address, i, mm_rqs[i].size))
        {
          printf(BLUE, "test_mm ERROR\n");
          return -1;
        }

    // Free
    for (i = 0; i < rq; i++)
      if (mm_rqs[i].address)
        free(mm_rqs[i].address);
  }
  return 0;
}