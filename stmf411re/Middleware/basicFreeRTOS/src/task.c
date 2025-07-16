#include "task.h"

List_t pxReadyTasksLists[configMAX_PRIORITIES];
List_t xDelayedTaskList;
volatile TickType_t xTickCount = 0;

BaseType_t xTaskCreate(TaskFunction_t pxTaskCode,
                       const char * const pcName,
                       const uint16_t usStackDepth,
                       void * const pvParameters,
                       UBaseType_t uxPriority,
                       TaskHandle_t * const pxCreatedTask )
{
    TCB_t *pxNewTCB;
    StackType_t *pxStack;

    pxNewTCB = pvPortMalloc(sizeof(TCB_t));
    pxStack = pvPortMalloc(sizeof(StackType_t) * usStackDepth);

    pxNewTCB->pxStack = pxStack;
    pxNewTCB->uxPriority = uxPriority;
    strncpy(pxNewTCB->pcTaskName, pcName, configMAX_TASK_NAME_LEN);

    pxNewTCB->pxTopOfStack = pxPortInitialiseStack(pxStack + usStackDepth - 1,
                                                   pxTaskCode, pvParameters);

    vListInsertEnd(&pxReadyTasksLists[uxPriority], &(pxNewTCB->xStateListItem));

    if (pxCreatedTask != NULL)
        *pxCreatedTask = (TaskHandle_t) pxNewTCB;

    return pdPASS;
}

void vTaskSwitchContext(void)
{
    UBaseType_t uxTopPriority = 0;
    pxCurrentTCB = (TCB_t *) listGET_OWNER_OF_HEAD_ENTRY(&pxReadyTasksLists[uxTopPriority]);
}

BaseType_t xTaskIncrementTick(void)
{
    return pdFALSE;
}

void vTaskStepTick(TickType_t ticksToJump) {
}

eSleepModeStatus eTaskConfirmSleepModeStatus(void) {
    return eStandardSleep;
}

void vTaskDelay(const TickType_t xTicksToDelay)
{
    TickType_t xTimeToWake = xTickCount + xTicksToDelay;

    uxListRemove(&(pxCurrentTCB->xStateListItem));

    listSET_LIST_ITEM_VALUE(&(pxCurrentTCB->xStateListItem), xTimeToWake);
    vListInsert(&xDelayedTaskList, &(pxCurrentTCB->xStateListItem));

    portYIELD();
}

static void prvIdleTask(void *pvParameters)
{
    for( ;; )
    {
        portYIELD();
    }
}