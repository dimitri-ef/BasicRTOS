#ifndef __SECURE_HEAP_H__
#define __SECURE_HEAP_H__

#include <stdlib.h>

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

/**
 * @brief Get the free heap size.
 *
 * @return Free heap size.
 */
size_t xPortGetFreeHeapSize( void );

/**
 * @brief Get the minimum ever free heap size.
 *
 * @return Minimum ever free heap size.
 */
size_t xPortGetMinimumEverFreeHeapSize( void );

#endif /* __SECURE_HEAP_H__ */