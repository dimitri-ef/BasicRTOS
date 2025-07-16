#ifndef __LIST_H__
#define __LIST_H__

#include "basicFreeRTOS.h"

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

#define listSET_LIST_ITEM_OWNER( pxListItem, pxOwner )      ( ( pxListItem )->pvOwner = ( void * ) ( pxOwner ) )
#define listGET_LIST_ITEM_OWNER( pxListItem )               ( ( pxListItem )->pvOwner )
#define listSET_LIST_ITEM_VALUE( pxListItem, xValue )       ( ( pxListItem )->xItemValue = ( xValue ) )
#define listGET_LIST_ITEM_VALUE( pxListItem )               ( ( pxListItem )->xItemValue )
#define listGET_ITEM_VALUE_OF_HEAD_ENTRY( pxList )          ( ( ( pxList )->xListEnd ).pxNext->xItemValue )
#define listGET_HEAD_ENTRY( pxList )                        ( ( ( pxList )->xListEnd ).pxNext )
#define listGET_NEXT( pxListItem )                          ( ( pxListItem )->pxNext )
#define listGET_END_MARKER( pxList )                        ( ( ListItem_t const * ) ( &( ( pxList )->xListEnd ) ) )
#define listLIST_IS_EMPTY( pxList )                         ( ( ( pxList )->uxNumberOfItems == ( UBaseType_t ) 0 ) ? pdTRUE : pdFALSE )
#define listCURRENT_LIST_LENGTH( pxList )                   ( ( pxList )->uxNumberOfItems )
#define listGET_OWNER_OF_HEAD_ENTRY( pxList )               ( ( &( ( pxList )->xListEnd ) )->pxNext->pvOwner )

void vListInitialise(List_t * const pxList);
void vListInitialiseItem(ListItem_t * const pxItem);
void vListInsert(List_t * const pxList, ListItem_t * const pxNewListItem);
void vListInsertEnd(List_t * const pxList, ListItem_t * const pxNewListItem);
UBaseType_t uxListRemove(ListItem_t * const pxItemToRemove);

#endif // __LIST_H__