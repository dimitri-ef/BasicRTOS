#ifndef __KERNEL_H__
#define __KERNEL_H__

#include <stdint.h>

typedef void (*task_function_t)(void*);

typedef struct tcb
{
    uint32_t priority;
    uint32_t *stack;

} tcb;


void xTaskCreate(task_function_t task, uint32_t stack_size, uint32_t priority);
void vTaskDelete();

#endif // __KERNEL_H__