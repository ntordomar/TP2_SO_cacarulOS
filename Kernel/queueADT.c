#include <queueADT.h>
#include <heap.h>

// Create a new Queue
Queue *createQueue()
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

// Adding an element to the queue
void enqueue(Queue *queue, PCB *data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        return;
    }
    newNode->data = data;
    newNode->next = NULL;

    if (queue->rear == NULL)
    {
        queue->front = newNode;
        queue->rear = newNode;
    }
    else
    {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

// peek function
PCB *peek(Queue *queue)
{
    if (isEmpty(queue))
    {
        return NULL; // Indicates an empty queue
    }
    return queue->front->data;
}

// Deletes and returns the first node
PCB *dequeue(Queue *queue)
{
    if (isEmpty(queue))
    {
        return NULL; // Empty queue
    }
    Node *temp = queue->front;
    PCB * data = temp->data;
    queue->front = queue->front->next;

    if (queue->front == NULL)
    {
        queue->rear = NULL;
    }
    free(temp);
    return data;
}

// Check if the queue is empty
int isEmpty(Queue *queue)
{
    return queue->front == NULL;
}

// Frees the memory used by the queue
void destroyQueue(Queue *queue)
{
    while (!isEmpty(queue))
    {
        dequeue(queue);
    }
    free(queue);
}

PCB *findElement(Queue *queue)
{
    Node *current = queue->front;
    while (current != NULL)
    {
        if (current->data->process->status == READY)
        {
            return current->data;
        }
        current = current->next;
    }

    return NULL; // Not found
}

PCB *findElementByPid(Queue *queue, int pid)
{
    Node *current = queue->front;
    while (current != NULL)
    {
        if (current->data->process->pid == pid)
        {
            return current->data;
        }
        current = current->next;
    }

    return NULL; // Not found
}

PCB *dequeueByData(Queue *queue, int pid)
{
    Node *current = queue->front;
    Node *prev = NULL;

    while (current != NULL)
    {
        if (current->data->process->pid == pid)
        {
            PCB *deletedData = current->data;

            if (current == queue->front)
                queue->front = current->next;

            if (current == queue->rear)
                queue->rear = prev;

            if (prev != NULL)
                prev->next = current->next;

            return deletedData;
        }

        prev = current;
        current = current->next;
    }

    return NULL; // Not found
}

int retPids(Queue *queue, int * pids)
{
    Node *current = queue->front;
    int i = 0;
    while (current != NULL)
    {
        pids[i] = current->data->process->pid;
        i++;
        current = current->next;
    }
    return i;
}

int * dequeueAllChildren(Queue * queue, int ppid)
{
    int *pids = malloc(sizeof(int)*100);
    int dim = 0;
    Node *current = queue->front;

    while (current != NULL)
    {
        if (current->data->process->parent == ppid)
        {
            pids[dim++] = current->data->process->pid;
        }
        current = current->next;
    }
    
    pids[dim] = -1;
    return pids;
}