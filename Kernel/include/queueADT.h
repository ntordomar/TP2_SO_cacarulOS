#include "../types.h"

typedef struct node
{
    PCB *data;
    struct node *next;
} Node;

typedef struct queue
{
    Node *front;
    Node *rear;
} Queue;

Queue *createQueue();
void enqueue(Queue *queue, PCB *data);
PCB *dequeue(Queue *queue);
int isEmpty(Queue *queue);
void destroyQueue(Queue *queue);
PCB *peek(Queue *queue);
PCB *findElement(Queue *queue);
PCB *findElementByPid(Queue *queue, int pid);
PCB *dequeueByData(Queue *queue, int pid);
int retPids(Queue *queue, int *pids);
int *dequeueAllChildren(Queue *queue, int ppid);