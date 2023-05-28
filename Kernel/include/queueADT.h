#include "../types.h"
#include <heap.h>
// Estructura para el nodo de la cola
typedef struct node {
    PCB* data;
    struct node* next;
} Node;

// Estructura para la cola
typedef struct queue {
    Node* front;
    Node* rear;
} Queue;

// Funciones para operar la cola
Queue* createQueue();
void enqueue(Queue* queue, PCB* data);
PCB* dequeue(Queue* queue);
int isEmpty(Queue* queue);
void destroyQueue(Queue* queue);
PCB* peek(Queue* queue);
PCB* findElement(Queue* queue);
PCB* findElementByPid(Queue* queue, int pid);
PCB* dequeueByData(Queue* queue, int pid);