#ifndef __TASK_C__
#define __TASK_C__

#include <string.h>

#include "list.h"

typedef struct tskTaskControlBlock       /* The old naming convention is used to prevent breaking kernel aware debuggers. */
{
    volatile StackType_t * pxTopOfStack;        /**< Points to the location of the last item placed on the tasks stack.  THIS MUST BE THE FIRST MEMBER OF THE TCB STRUCT. */
    ListItem_t xStateListItem;                  /**< The list that the state list item of a task is reference from denotes the state of that task (Ready, Blocked, Suspended ). */
    ListItem_t xEventListItem;                  /**< Used to reference a task from an event list. */
    UBaseType_t uxPriority;                     /**< The priority of the task.  0 is the lowest priority. */
    StackType_t * pxStack;                      /**< Points to the start of the stack. */
    char pcTaskName[ configMAX_TASK_NAME_LEN ]; /**< Descriptive name given to the task when created.  Facilitates debugging only. */
} tskTCB;

typedef tskTCB TCB_t;

static TCB_t * volatile pxCurrentTCB = NULL;

struct tskTaskControlBlock;
typedef struct tskTaskControlBlock         * TaskHandle_t;

typedef enum
{
    eSleepModeStatusDummy1,
    eSleepModeStatusDummy2,
    eAbortSleep,
    eStandardSleep
} eSleepModeStatus;

BaseType_t xTaskCreate(TaskFunction_t pxTaskCode,
                       const char * const pcName,
                       const uint16_t usStackDepth,
                       void * const pvParameters,
                       UBaseType_t uxPriority,
                       TaskHandle_t * const pxCreatedTask );
void vTaskSwitchContext(void);
BaseType_t xTaskIncrementTick(void);
void vTaskStepTick(TickType_t ticksToJump);
eSleepModeStatus eTaskConfirmSleepModeStatus(void);
void vTaskDelay(const TickType_t xTicksToDelay);

#endif // __TASK_C__