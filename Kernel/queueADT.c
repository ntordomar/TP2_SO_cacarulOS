#include <queueADT.h>

// Crear una nueva cola
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

// Agregar un elemento a la cola
void enqueue(Queue* queue, PCB* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL) {
        return;
    }
    newNode->data = data;
    newNode->next = NULL;

    if(queue->rear == NULL) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

//peek function
PCB* peek(Queue* queue) {
    if(isEmpty(queue)) {
        return -1;  // Valor centinela para indicar una cola vacía
    }
    return queue->front->data;
}

// Eliminar y devolver el elemento de la parte frontal de la cola
PCB* dequeue(Queue* queue) {
    if(isEmpty(queue)) {
        return -1;  // Valor centinela para indicar una cola vacía
    }
    Node* temp = queue->front;
    int data = temp->data;
    queue->front = queue->front->next;

    if(queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return data;
}

// Verificar si la cola está vacía
int isEmpty(Queue* queue) {
    return queue->front == NULL;
}

// Liberar la memoria utilizada por la cola
void destroyQueue(Queue* queue) {
    while(!isEmpty(queue)) {
        dequeue(queue);
    }
    free(queue);
}

PCB* findElement(Queue* queue) {
    Node* current = queue->front;
    while(current != NULL) {
        if(current->data->process->status == READY) {
            return current->data;
        }
        current = current->next;
    }

    return NULL;  // Valor centinela para indicar que el elemento no fue encontrado
}

PCB* findElementByPid(Queue* queue, int pid){
    Node* current = queue->front;
    while(current != NULL) {
        if(current->data->process->pid == pid) {
            return current->data;
        }
        current = current->next;
    }

    return NULL;  // Valor centinela para indicar que el elemento no fue encontrado
}

PCB* dequeueByData(Queue* queue, int pid) {
    Node* current = queue->front;
    Node* prev = NULL;

    while (current != NULL) {
        if (current->data->process->pid == pid) {
            PCB* deletedData = current->data;

            if (current == queue->front)
                queue->front = current->next;

            if (current == queue->rear)
                queue->rear = prev;

            if (prev != NULL)
                prev->next = current->next;

            free(current);
            return deletedData;
        }

        prev = current;
        current = current->next;
    }

    return NULL;  // Valor sentinela para indicar que el proceso no fue encontrado
}
