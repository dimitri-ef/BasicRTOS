#include "task.h"

List_t * const pxReadyTasksLists[configMAX_PRIORITIES];
List_t const xDelayedTasksLists;

static TCB_t * volatile pxCurrentTCB = NULL;

typedef struct tskTaskControlBlock       /* The old naming convention is used to prevent breaking kernel aware debuggers. */
{
    volatile StackType_t * pxTopOfStack;        /**< Points to the location of the last item placed on the tasks stack.  THIS MUST BE THE FIRST MEMBER OF THE TCB STRUCT. */
    ListItem_t xGenericListItem;                
    UBaseType_t uxPriority;                     /**< The priority of the task.  0 is the lowest priority. */
    StackType_t * pxStack;                      /**< Points to the start of the stack. */
    char pcTaskName[ configMAX_TASK_NAME_LEN ]; /**< Descriptive name given to the task when created.  Facilitates debugging only. */
} tskTCB;

typedef tskTCB TCB_t;

static TCB_t *prvAllocateTCBAndStack(uint16_t usStackDepth)
{
    TCB_t *pxTCB = pvPortMalloc(sizeof(tskTCB));
    pxTCB->pxStack = pvPortMalloc(sizeof(usStackDepth));

    return pxTCB;
}

BaseType_t xTaskCreate(TaskFunction_t pxTaskCode, const char * const pcName, uint16_t usStackDepth,
    void *pvParameters, UBaseType_t uxPriority, TaskHandle_t *pxCreatedTask)
{
    TCB_t *pxTCB = prvAllocateTCBAndStack(usStackDepth);
    

    vListInsert(&pxReadyTasksLists[uxPriority], &(pxTCB->xGenericListItem));
}

void vTaskDelay(const TickType_t xTicksToDelay)
{
    pxCurrentTCB->xGenericListItem.xItemValue = xTicksToDelay;
    vListInsert(&xDelayedTasksLists, pxCurrentTCB->xGenericListItem);
}

void vTaskStartScheduler(void)
{
    prvInitialiseTaskLists();

    prvCreateIdleTask();

    xPortStartScheduler();
}


static void prvCreateIdleTask(void)
{
    xTaskCreate(prvIdleTask, "IDLE", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, &xIdleTaskHandle);
}


static void prvIdleTask(void *pvParameters)
{
    for( ;; )
    {
        prvCheckTasksWaitingTermination();

        portYIELD();
    }
}