#include "list.h"

void vListInitialise(List_t * const pxList)
{
    pxList->uxNumberOfItems = 0U;

    pxList->pxIndex = &(pxList->xListEnd);

    pxList->xListEnd.xItemValue = portMAX_DELAY;
    pxList->xListEnd.pxNext = &(pxList->xListEnd);
    pxList->xListEnd.pxPrevious = &(pxList->xListEnd);
}

void vListInitialiseItem(ListItem_t * const pxItem)
{
    pxItem->pvContainer = NULL;
}

void vListInsert(List_t * const pxList, ListItem_t * const pxNewListItem)
{
    ListItem_t *pxIterator;
    const TickType_t xValueOfInsertion = pxNewListItem->xItemValue;

    pxIterator = (ListItem_t *) &(pxList->xListEnd);

    while (pxIterator->pxNext->xItemValue <= xValueOfInsertion)
    {
        pxIterator = pxIterator->pxNext;
    }

    pxNewListItem->pxNext = pxIterator->pxNext;
    pxNewListItem->pxPrevious = pxIterator;
    pxIterator->pxNext->pxPrevious = pxNewListItem;
    pxIterator->pxNext = pxNewListItem;

    pxNewListItem->pvContainer = pxList;
    pxList->uxNumberOfItems++;
}

void vListInsertEnd(List_t * const pxList, ListItem_t * const pxNewListItem)
{
    pxNewListItem->pxNext = &(pxList->xListEnd);
    pxNewListItem->pxPrevious = pxList->xListEnd.pxPrevious;
    pxNewListItem->pvContainer = pxList;

    pxList->xListEnd.pxPrevious->pxNext = pxNewListItem;
    pxList->xListEnd.pxPrevious = pxNewListItem;
    pxList->uxNumberOfItems++;
}

UBaseType_t uxListRemove(ListItem_t * const pxItemToRemove)
{
    List_t * const pxList = pxItemToRemove->pvContainer;

    pxItemToRemove->pxNext->pxPrevious = pxItemToRemove->pxPrevious;
    pxItemToRemove->pxPrevious->pxNext = pxItemToRemove->pxNext;

    if (pxList->pxIndex == pxItemToRemove)
    {
        pxList->pxIndex = pxItemToRemove->pxPrevious;
    }

    pxItemToRemove->pvContainer = NULL;
    pxList->uxNumberOfItems--;

    return pxList->uxNumberOfItems;
}