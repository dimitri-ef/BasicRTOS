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

/**
 * Must be called before a list is used!  This initialises all the members
 * of the list structure and inserts the xListEnd item into the list as a
 * marker to the back of the list.
 *
 * @param pxList Pointer to the list being initialised.
 *
 * \page vListInitialise vListInitialise
 * \ingroup LinkedList
 **/
void vListInitialise(List_t * const pxList);

/**
 * Must be called before a list item is used.  This sets the list container to
 * null so the item does not think that it is already contained in a list.
 *
 * @param pxItem Pointer to the list item being initialised.
 *
 * \page vListInitialiseItem vListInitialiseItem
 * \ingroup LinkedList
 **/
void vListInitialiseItem(ListItem_t * const pxItem);

/**
 * Insert a list item into a list.  The item will be inserted into the list in
 * a position determined by its item value (ascending item value order).
 *
 * @param pxList The list into which the item is to be inserted.
 *
 * @param pxNewListItem The item that is to be placed in the list.
 *
 * \page vListInsert vListInsert
 * \ingroup LinkedList
 **/
void vListInsert(List_t * const pxList, ListItem_t * const pxNewListItem);

/**
 * Insert a list item into a list.  The item will be inserted in a position
 * such that it will be the last item within the list returned by multiple
 * calls to listGET_OWNER_OF_NEXT_ENTRY.
 *
 * The list member pxIndex is used to walk through a list.  Calling
 * listGET_OWNER_OF_NEXT_ENTRY increments pxIndex to the next item in the list.
 * Placing an item in a list using vListInsertEnd effectively places the item
 * in the list position pointed to by pxIndex.  This means that every other
 * item within the list will be returned by listGET_OWNER_OF_NEXT_ENTRY before
 * the pxIndex parameter again points to the item being inserted.
 *
 * @param pxList The list into which the item is to be inserted.
 *
 * @param pxNewListItem The list item to be inserted into the list.
 *
 * \page vListInsertEnd vListInsertEnd
 * \ingroup LinkedList
 **/
void vListInsertEnd(List_t * const pxList, ListItem_t * const pxNewListItem);

/**
 * Remove an item from a list.  The list item has a pointer to the list that
 * it is in, so only the list item need be passed into the function.
 *
 * @param uxListRemove The item to be removed.  The item will remove itself from
 * the list pointed to by it's pxContainer parameter.
 *
 * @return The number of items that remain in the list after the list item has
 * been removed.
 *
 * \page uxListRemove uxListRemove
 * \ingroup LinkedList
 **/
UBaseType_t uxListRemove(ListItem_t * const pxItemToRemove);

#endif // __LIST_H__