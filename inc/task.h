#ifndef __TASK_C__
#define __TASK_C__

static List_t pxReadyTasksLists[ configMAX_PRIORITIES ];
static List_t * volatile pxDelayedTaskList;

typedef struct tskTaskControlBlock
{
    volatile StackType_t * pxTopOfStack;
    ListItem_t xStateListItem;
    UBaseType_t uxPriority;
    StackType_t * pxStack;
    char pcTaskName[ configMAX_TASK_NAME_LEN ];
} tskTCB;

#endif // __TASK_C__