#include "task.h"

List_t * const pxReadyTasksLists[configMAX_PRIORITIES];

typedef struct tskTaskControlBlock       /* The old naming convention is used to prevent breaking kernel aware debuggers. */
{
    volatile StackType_t * pxTopOfStack;        /**< Points to the location of the last item placed on the tasks stack.  THIS MUST BE THE FIRST MEMBER OF THE TCB STRUCT. */
    ListItem_t xStateListItem;                  /**< The list that the state list item of a task is reference from denotes the state of that task (Ready, Blocked, Suspended ). */
    UBaseType_t uxPriority;                     /**< The priority of the task.  0 is the lowest priority. */
    StackType_t * pxStack;                      /**< Points to the start of the stack. */
    char pcTaskName[ configMAX_TASK_NAME_LEN ]; /**< Descriptive name given to the task when created.  Facilitates debugging only. */
} tskTCB;

typedef tskTCB TCB_t;

BaseType_t xTaskCreate(TaskFunction_t pxTaskCode, const char * const pcName, configSTACK_DEPTH_TYPE usStackDepth,
    void *pvParameters, UBaseType_t uxPriority, TaskHandle_t *pxCreatedTask)
{
    TCB_t *pxNewTCB = pvPortMalloc();

    

    vListInsert(&pxReadyTasksLists[uxPriority], &(pxNewTCB->xGenericListItem));
}


BaseType_t vTaskStartScheduler(void)
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