#ifdef BUDDY

#include <buddyMemManager.h>
#include <heap.h>
#include <bTree.h>

int log2(uint32_t number);
int getFreeBlock(uint8_t minBlockRequired);
size_t getMinOrder(size_t realSize);
listType *getBuddy(listType *node);
listType *getBlockAddress(listType *node);

#define minAlloc 4
#define maxAlloc 31

static listType orders[maxAlloc - minAlloc];
static uint8_t currentBlocks;
static size_t blockMaxSize;

static listType* base;
int init = 0;

void initHeap() {
    if (!init) {
        init = 1;
        base = (listType *) 0x600000;
    }

    blockMaxSize = TOTALHEAPSIZE;
    currentBlocks = log2(blockMaxSize) - minAlloc + 1;

    if (currentBlocks > (maxAlloc - minAlloc)) {
        currentBlocks = maxAlloc - minAlloc;
    }

    for (int i = 0; i < currentBlocks; i++) {
        initList(&orders[i]);
        orders[i].free = 0;
        orders[i].order = i;
    }

    addNodeToOrder(&orders[currentBlocks - 1], base, currentBlocks - 1);
}

void * malloc(size_t size) {
    if (!init) {
        initHeap();
    }


    size_t realSize = size + sizeof(listType);

    if (size == 0 || realSize > blockMaxSize) {
        return NULL;
    }

    uint8_t lowerOrder = getMinOrder(realSize);

    int freeBlock = getFreeBlock(lowerOrder);

    if (freeBlock == -1) {
        return NULL;
    }

    if (orders[freeBlock].prev != NULL || orders[freeBlock].next != NULL) {
        listType * node = pop(&orders[freeBlock]);
        
        for (; freeBlock > lowerOrder; freeBlock--) {
            node->order--;
            addNodeToOrder(&orders[freeBlock - 1], getBuddy(node), freeBlock - 1);
        }

        node->free = 0;
        return (void *) (node + 1);

    }

    return NULL;

}

memoryInfo * getHeapInfo() {
    memoryInfo * info = (memoryInfo *) malloc(sizeof(memoryInfo));
    info->total = TOTALHEAPSIZE;
    info->used = 0;
    info->free = 0;
    for (int i = 0; i < currentBlocks; i++) {
        listType * node = orders[i].next;
        while (node != &orders[i]) {
            if (node->free) {
                info->free += 1 << i;
            } else {
                info->used += 1 << i;
            }
            node = node->next;
        }
    }
    return info;
}

void free(void *ptr){
    if (ptr == NULL)
        return;

  listType *freeNode = (listType *)ptr - 1;
  freeNode->free = 1;

  listType *freeBuddyBlock = getBuddy(freeNode);

  // si libero bloques, uno los que quedaron vacios
  while (freeNode->order != currentBlocks - 1 && freeBuddyBlock->order == freeNode->order && freeBuddyBlock->free)
  {
    removeNode(freeBuddyBlock);
    freeNode = getBlockAddress(freeNode);
    freeNode->order++;
    freeBuddyBlock = getBuddy(freeNode);
  }

  push(&orders[freeNode->order], freeNode);
}

void addNodeToOrder(listType *blockList, listType *node, uint8_t blockOrder)
{
  node->order = blockOrder;
  node->free = 1;
  push(blockList, node);
}

int getFreeBlock(uint8_t minBlockRequired)
{
  uint8_t freeBlock;

  for (freeBlock = minBlockRequired; freeBlock < currentBlocks && isListEmpty(&orders[freeBlock]); freeBlock++)
    ;

  if (freeBlock > currentBlocks)
    return -1;
  return freeBlock;
}

int log2(uint32_t number)
{
  if (number == 0)
  {
    return -1;
  }

  int result = -1;
  while (number)
  {
    result++;
    number >>= 1;
  }
  return result;
}

size_t getMinOrder(size_t realSize) {
    size_t min = (size_t) log2(realSize);

    if (min < minAlloc) {
        return 0;
    }
    min -= minAlloc;
    if (realSize && !(realSize & (realSize - 1))) {
        return min;
    }
    return min + 1;
}

listType *getBuddy(listType *node)
{
  uint8_t order = node->order;
  uintptr_t currentOffset = (uintptr_t)node - (uintptr_t)base;
  intptr_t newOffest = currentOffset ^ (1 << (minAlloc + order));

  return (listType *)((uintptr_t)base + newOffest);
}

listType *getBlockAddress(listType *node)
{
  uint8_t order = node->order;
  uintptr_t mask = (1 << (minAlloc + order));
  mask = ~mask;
  uintptr_t currentOffset = (uintptr_t)node - (uintptr_t)base;
  intptr_t newOffest = currentOffset & mask;

  return (listType *)(newOffest + (uintptr_t)base);
}
#endif