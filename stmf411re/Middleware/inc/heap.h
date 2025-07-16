#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include <stdint.h>

#ifndef HEAP_SIZE
    #define HEAP_SIZE    ( ( ( size_t ) ( 10 * 1024 ) ) )
#endif

#define ALIGN_BYTES     8
#define ALIGN_MASK      (ALIGN_BYTES - 1)

extern uint8_t ucHeap[ HEAP_SIZE ];

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
extern BlockLink_t xStart;
extern BlockLink_t * pxEnd;

extern size_t xFreeBytesRemaining;

/**
 * @brief Allocates memory from heap.
 *
 * @param[in] xWantedSize The size of the memory to be allocated.
 *
 * @return Pointer to the memory region if the allocation is successful, NULL
 * otherwise.
 */
void * pvPortMalloc( size_t xWantedSize );

/**
 * @brief Frees the previously allocated memory.
 *
 * @param[in] pv Pointer to the memory to be freed.
 */
void vPortFree( void * pv );

#endif /* __HEAP_H__ */