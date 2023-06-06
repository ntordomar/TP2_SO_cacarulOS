// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <userStdF.h>
#include <user_syscalls.h>
#include <stdint.h>
#include <userLib.h>

#define MAX_PHYLOS 15
#define MIN_PHYLOS 5
#define LEFT    (i + currentCount - 1) % currentCount
#define RIGHT   (i + 1) % currentCount
#define THINKING    0
#define HUNGRY      1
#define EATING      2

#define TRUE 1
#define FALSE (!TRUE)

#define MUTEX 777
#define PRINT_MUTEX 888

typedef int sem_t;
int end = FALSE;

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
    end = FALSE;
    currentCount = 0;
    semDestroy("mutex");
    semDestroy("print");
    mutexId = semCreate("mutex", 1);
    printId = semCreate("print", 1);
    sys_sem_open("mutex");
    sys_sem_open("print");
 
    for(int i = 0 ; i < MIN_PHYLOS; i++){
        addPhylo();
    }

    char c;
    while(!end){
        c = getChar();
        switch(c){
            case 'A':
                addPhylo();
                break;
            case 'R':
                removePhylo();
                break;
            case 'Q':
                end = TRUE;
                break;
        }
    }

    for(int i = 0 ; i < currentCount; i++){
        sys_kill(pids[i]);
        semDestroy(s[i]);
        semDestroy(safe[i]);
    }

    semDestroy("mutex");
    semDestroy("print");

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
        philos = args;
        int fds[2] = {0,0};
        pids[currentCount] = sys_create_process("phylo", philos, &philosopher, 0, fds);
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
    for(int i = 0; i < 5000000; i++)
        ;
    semWait(printId);
    for(int i = 0; i < currentCount; i++) {
        print(state[i] == EATING? "E " : ". ", 2);
    }
    semPost(printId);
}

void think() {
    for(int i = 0; i < 5000000; i++)
        ;
}