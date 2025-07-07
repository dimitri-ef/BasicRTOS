#include "heap.h"

#ifndef HEAP_SIZE
    #define secureconfigTOTAL_HEAP_SIZE    ( ( ( size_t ) ( 10 * 1024 ) ) )
#endif

static uint8_t ucHeap[ secureconfigTOTAL_HEAP_SIZE ];

/**
 * @brief The linked list structure.
 *
 * This is used to link free blocks in order of their memory address.
 */
typedef struct A_BLOCK_LINK
{
    struct A_BLOCK_LINK * pxNextFreeBlock; /**< The next free block in the list. */
    size_t xBlockSize;                     /**< The size of the free block. */
} BlockLink_t;

/**
 * @brief Create a couple of list links to mark the start and end of the list.
 */
static BlockLink_t xStart;
static BlockLink_t * pxEnd = NULL;

void *pvPortMalloc(size_t xWantedSize)
{
    
}

void vPortFree(void *pv)
{
}
