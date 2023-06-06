// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <bTree.h>
#include <stddef.h>
void initList(listType * list) {
    list->next = list;
    list->prev = list;
}


void push(listType * list, listType * node) {
    listType * prev = list->prev;
    node->prev = prev;
    node->next = list;
    prev->next = node;
    list->prev = node;
}
listType * pop(listType * list) {
    listType * node = list->prev;
    if (node == list) {
        return NULL;
    }
    removeNode(node);
    return node;
}
void removeNode(listType * node) {
    listType * prev = node->prev;
    listType * next = node->next;
    prev->next = next;
    next->prev = prev;
}

char isListEmpty(listType * list) {
    return list->prev == list;
}