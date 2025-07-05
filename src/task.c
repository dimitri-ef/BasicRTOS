#include "task.h"

List_t * const pxReadyTasksLists[configMAX_PRIORITIES];

BaseType_t xTaskCreate(TaskFunction_t pxTaskCode, const char * const pcName, configSTACK_DEPTH_TYPE usStackDepth,
    void *pvParameters, UBaseType_t uxPriority, TaskHandle_t *pxCreatedTask)
{
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