#include <phylo.h>
#include <userlandApps.h>
#include <user_syscalls.h>

#define LEFT(i) (((i) + currentPhilosophers - 1) % currentPhilosophers)
#define RIGHT(i) (((i) + 1) % currentPhilosophers)

phyloType philosopher[MAX_PHYLO] = {{0}};

static int currentPhilosophers = 0;

static int phyloSem;

static void testEat(int64_t index)
{
  if (philosopher[index].state == WAITING && philosopher[LEFT(index)].state != EATING && philosopher[RIGHT(index)].state != EATING)
  {
    philosopher[index].state = EATING;
    semPost(philosopher[index].semId);
  }
}

void philoWait(int64_t index)
{
  semWait(phyloSem);
  philosopher[index].state = WAITING;
  testEat(index);
  semPost(phyloSem);
  semWait(philosopher[index].semId);
}

void philoRest(int64_t index)
{
  semWait(phyloSem);
  philosopher[index].state = THINKING;
  testEat(LEFT(index));
  testEat(RIGHT(index));
  semPost(phyloSem);
}

void philoMain(unsigned int argc, char *argv[])
{
  int64_t index = satoi(argv[1]);
  while (1)
  {
    philoWait(index);
    hold(EATING);
    philoRest(index);
    hold(THINKING);
  }
}

int startPhiloProcess()
{
  philosopher[currentPhilosophers].state = THINKING;
  char ** args = malloc(3 * sizeof(char *));
  args[0] = NULL;
  args[1] = NULL;
  args[2] = NULL;
  int fds[2] = {0, 0};
  int processPid = sys_create_process("phylo",args, &philoMain, 0, fds);
  if (processPid == -1)
  {
    semClose(philosopher[currentPhilosophers].semId);
    semDestroy(philosopher[currentPhilosophers].semId);
    return -1;
  }
  philosopher[currentPhilosophers].pid = processPid;
  currentPhilosophers += 1;
  return 0;
}

int addPhilosofer()
{
  if (currentPhilosophers == MAX_PHYLO)
  {
    return -1;
  }

  int semaphore = semCreateAnonymous(1);
  if (semaphore == -1)
  {
    return -1;
  }
  philosopher[currentPhilosophers].semId = semaphore;

  semWait(phyloSem);
  startPhiloProcess();
  semPost(phyloSem);
  return 0;
}

void freePhilosofer(int index)
{
  kill(philosopher[index].pid);
  semClose(philosopher[index].semId);
  semDestroy(philosopher[index].semId);
}

int removePhilosofer()
{
  if (currentPhilosophers == INITIAL_PHYLO)
  {
    return -1;
  }

  semWait(phyloSem);
  freePhilosofer(currentPhilosophers - 1);
  currentPhilosophers -= 1;
  semPost(phyloSem);
  return 0;
}

void printTable()
{
  while (1)
  {
    semWait(phyloSem);
    for (int i = 0; i < currentPhilosophers; i += 1)
    {
      if (philosopher[i].state == EATING)
        printChar('E',WHITE);
      else
        printChar('.',WHITE);
    }
    printf(WHITE,"\n");
    semPost(phyloSem);
    hold(60);
  }
}

int phylo(char **  arguments)
{
  phyloSem = semCreate("philosophers",1);
  if (phyloSem == -1)
    return;

  currentPhilosophers = 0;

  printf(WHITE, "Press the key");
  printf(BLUE, "a");
  printf(WHITE, "to add a dining philosopher. \n");
  printf(WHITE, "Press the key");
  printf(BROWN, "d");
  printf(WHITE, "to delete a dining philosopher. \n");
  printf(WHITE, "Press the key");
  printf(GREEN, "q");
  printf(WHITE, "to quit the table. \n");

  semWait(phyloSem);
  for (int i = 0; i < INITIAL_PHYLO; i += 1)
  {
    int semaphore = semCreateAnonymous(1);
    if (semaphore == -1)
    {
      printf(RED, "ERROR: cannot initialize semaphore.\n");
      return;
    }
    philosopher[i].semId = semaphore;
  }
  for (int i = 0; i < INITIAL_PHYLO; i += 1)
  {
    if (startPhiloProcess() == -1)
    {
      printf(RED, "ERROR: Cannot initialize de phylo process.\n");
      return;
    }
  }

  char **args;
  args = malloc(3 * sizeof(char *));
  args[0] = NULL;
  args[1] = NULL;
  args[2] = NULL;
  int fds[2] = {0, 0};
  int tablePid = sys_create_process("printTable", args, &printTable, 1, fds);
  if (tablePid == -1)
  {
    printf(RED,"The table could not be created\n");
    return;
  }
  semPost(phyloSem);
  while (1)
  {
    char c = getChar();
    if (c == 'A')
    {
      int addedPhilo = addPhilosofer();
      if (addedPhilo == 0)
        printf(WHITE,"A new philosopher has arrived to the table \n" );
      else printf(RED, "There is no more space inthe table\n");
    }
    else if (c == 'D')
    {
      int removedPhilo = removePhilosofer();
      if (removedPhilo == 0)
        printf( WHITE,"A philosopher is done eating and is leaving the table \n");
      else
        printf(WHITE,"Minimum quantity if philosophers reached\n" );
    }
    else if (c == 'Q')
    {
      printf(WHITE,"cacarulo wants to be alone. Goodbye all" );
      break;
    }
  }
  for (int i = 0; i < currentPhilosophers; i += 1)
  {
    freePhilosofer(i);
  }
  kill(tablePid);
  semClose(phyloSem);
  semDestroy(phyloSem);
}