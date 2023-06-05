#define WAITING 0
#define THINKING 1
#define EATING 2

#define MAX_PHYLO 15
#define INITIAL_PHYLO 5

typedef struct
{
  int pid;
  int state;
  int semId;
} phyloType;
