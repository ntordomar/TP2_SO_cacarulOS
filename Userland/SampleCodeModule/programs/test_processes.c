// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <userLib.h>
#include <user_syscalls.h>
#include <test_util.h>
#include <userStdF.h>
#include <locale.h>

enum State { RUNNING,
             BLOCKED,
             KILLED };

typedef struct P_rq {
  int32_t pid;
  enum State state;
} p_rq;
int fdDefault[2] = {0,0};
int test_processes(char ** args) {
  uint8_t rq;
  uint8_t alive = 0;
  uint8_t action;
  uint64_t max_processes;
  char *argvAux[] = {NULL};

  if (args[0] == NULL){
    printf(RED,"test_processes: ERROR: missing argument\n");
    return -1;
  }
    

  if ((max_processes = satoi(args[0])) <= 0){
    printf(RED,"test_processes: ERROR: invalid argument\n");
    return -1;
  }
    

  p_rq p_rqs[max_processes];

  while (1) {

    // Create max_processes processes
    for (rq = 0; rq < max_processes; rq++) {
      for (int i = 0; i < 5000000 ; i ++){;}
      p_rqs[rq].pid = sys_create_process("endless_loop", argvAux, &endless_loop, 0,fdDefault);
      
      if (p_rqs[rq].pid == -1) {
        printf(RED,"test_processes: ERROR creating process\n");
        return -1;
      } else {
        p_rqs[rq].state = RUNNING;
        alive++;
      }
    }

    // Randomly kills, blocks or unblocks processes until every one has been killed
    while (alive > 0) {

      for (rq = 0; rq < max_processes; rq++) {
        action = GetUniform(100) % 2;

        switch (action) {
          case 0:
            if (p_rqs[rq].state == RUNNING || p_rqs[rq].state == BLOCKED) {
             
              if (sys_kill(p_rqs[rq].pid) == -1) {
                printf(RED,"test_processes: ERROR killing process\n");
                return -1;
              }
              
              sys_kill(p_rqs[rq].pid);
              
              
              p_rqs[rq].state = KILLED;
              alive--;
            }
            break;

          case 1:
            if (p_rqs[rq].state == RUNNING) {
              if (sys_block(p_rqs[rq].pid) == -1) {
                printf(RED,"test_processes: ERROR blocking process\n");
                return -1;
              }
              p_rqs[rq].state = BLOCKED;
            }
            break;
        }
      }

      // Randomly unblocks processes
      for (rq = 0; rq < max_processes; rq++)
        if (p_rqs[rq].state == BLOCKED && GetUniform(100) % 2) {
          if (sys_resume(p_rqs[rq].pid) == -1) {
            printf(RED,"test_processes: ERROR unblocking process\n");
            return -1;
          }
          p_rqs[rq].state = RUNNING;
        }
    }

  }
}