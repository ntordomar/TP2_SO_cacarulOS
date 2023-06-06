#include <user_syscalls.h>
#include <stdint.h>
#include <userLib.h>
#include <userlandApps.h>

#define MAX_PHYLOS 15
#define MIN_PHYLOS 5
#define LEFT    (i + currentCount - 1) % currentCount
#define RIGHT   (i + 1) % currentCount
#define THINKING    0
#define HUNGRY      1
#define EATING      2


#define MUTEX 777
#define PRINT_MUTEX 888

typedef int sem_t;
int end = 0;

int state[MAX_PHYLOS] = { 0 };
sem_t s[MAX_PHYLOS] = { 0 };
sem_t safe[MAX_PHYLOS] = { 0 };
int pids[MAX_PHYLOS] = { 0 };
int currentCount = 0;

int mutexId;
int printId;

int philosopher(char ** num);
void takeForks(int i);
void addPhylo();
void removePhylo();
void putForks(int i);
void test(int i);
void eat();
void think();

int phylo(char ** arguments) {

    printf(WHITE, "Welcome to the dining philosophers.\n");
    printf(WHITE, "Press A to add a philosopher.\n");
    printf(WHITE, "Press R to remove a philosopher.\n");
    printf(RED, "Press Q to quit.\n");

    end = 0;
    currentCount = 0;
    mutexId = semCreate("mutex", 1);
    printId = semCreate("print", 1);
    sys_sem_open("mutex");
    sys_sem_open("print");
 
    printf(WHITE, "Initializing...\n");
    hold(10);
    for(int i = 0 ; i < MIN_PHYLOS; i++){
        addPhylo();
    }

    char c;
    while(!end){
        c = getChar();
        switch(c){
            case 'A':
                printf(WHITE, "Adding a philosopher...\n");
                hold(5);
                addPhylo();
                break;
            case 'R':
                printf(WHITE, "Removing a philosopher...\n");
                hold(5);
                removePhylo();
                break;
            case 'Q':
                printf(WHITE, "Quiting...\n");
                end = 1;
                break;
        }
    }

    sys_waitpid(pids[0]);
    for(int i = 1 ; i < currentCount; i++){
        sys_kill(pids[i]);
        sys_kill(pids[i]);
        semDestroy(s[i]);
        semDestroy(safe[i]);
    }

    semDestroy(mutexId);
    semDestroy(printId);
    return 0;
}


void addPhylo(){

  
    semWait(mutexId);
    if(currentCount == MAX_PHYLOS){
        printf(RED,"MAX PHYLOS REACHED\n");
    } else{
        state[currentCount] = THINKING;
        s[currentCount] = semCreateAnonymous(0);
        safe[currentCount] = semCreateAnonymous(1);

        char string[12] = { "philosopher" };
        char ** philos = { 0 };

        char ** args = (char **) malloc(3 * sizeof(char *));
        char * buf = (char *) malloc(8);
        itoa(currentCount, buf, 10);

        args[0] = (char *) (intptr_t) strcpy(args[0], string);
        args[1] = buf;
        args[2] = NULL;
        philos = args;
        int fds[2] = {0,0};
        pids[currentCount] = sys_create_process(string, philos, &philosopher, 0, fds);
        if( pids[currentCount] <= 0) {
            printf(RED, "error creating philosopher. aborting\n");
            return;
        }


        currentCount++;
    }
    semPost(mutexId);
}

void removePhylo(){
    if(currentCount == MIN_PHYLOS){
        printf(WHITE,"MIN PHYLOS REACHED\n");
        return;
    }

    semWait(safe[currentCount-1]);
    semWait(mutexId);

    currentCount--;
    semClose(safe[currentCount]);
    semDestroy(safe[currentCount]);
    killProcess(pids[currentCount]);
    semClose(s[currentCount]);
    semDestroy(s[currentCount]);
    
    semPost(mutexId);
}

int philosopher(char ** num) {
    int i = atoi(num[1]);
    while(!end) {
        semWait(safe[i]);
        think();
        takeForks(i);
        eat();
        putForks(i);
        semPost(safe[i]);
    }
    return 0;
}


void takeForks(int i) {
    semWait(mutexId);
    state[i] = HUNGRY;
    test(i);
    semPost(mutexId);
    semWait(s[i]);
}


void putForks(int i) {
    semWait(mutexId);
    state[i] = THINKING;
    test(LEFT);
    test(RIGHT);
    semPost(mutexId);
}


void test(int i) {
    if(state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[i] = EATING;
        semPost(s[i]);
    }
}

void eat() {
    hold(10);
    semWait(printId);
    for(int i = 0; i < currentCount; i++) {
        printf(WHITE, state[i] == EATING? "E " : ". ", 2);
    }
    printf(WHITE, "\n");
    semPost(printId);
}

void think() {
    for(int i = 0; i < 50000; i++)
        ;
}