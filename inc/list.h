#ifndef __LIST_H__
#define __LIST_H__

#include <stddef.h>

typedef uint32_t UBaseType_t;

struct xLIST;
struct xLIST_ITEM
{
    volatile TickType_t xItemValue;
    struct xLIST_ITEM * volatile pxNext;
    struct xLIST_ITEM * volatile pxPrevious;
    void * pvOwner;
    struct xLIST * volatile pvContainer;
};
typedef struct xLIST_ITEM ListItem_t;

typedef struct xLIST
{
    volatile UBaseType_t uxNumberOfItems;
    ListItem_t * volatile pxIndex;
    ListItem_t xListEnd;
} List_t;

void vListInitialise(List_t * const pxList);

void vListInitialiseItem(ListItem_t * const pxItem);

void vListInsert(List_t * const pxList, ListItem_t * const pxNewListItem);

void vListInsertEnd(List_t * const pxList, ListItem_t * const pxNewListItem);

UBaseType_t uxListRemove(ListItem_t * const pxItemToRemove);

#endif // __LIST_H__