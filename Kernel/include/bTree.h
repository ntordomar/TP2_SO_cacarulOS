#include <stdint.h>

typedef struct listType
{
    struct listType *next;
    struct listType *prev;
    uint8_t order;
    uint8_t free;
} listType;

void initList(listType *list);
void push(listType *list, listType *node);
listType *pop(listType *list);
void removeNode(listType *node);
char isListEmpty(listType *list);