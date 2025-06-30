#ifndef __CIRCULAR_LINKED_LIST_H__
#define __CIRCULAR_LINKED_LIST_H__

#include <stddef.h>

typedef struct node {
    void *data;
    node *next;
    node *prev;
} node;

#endif // __CIRCULAR_LINKED_LIST_H__