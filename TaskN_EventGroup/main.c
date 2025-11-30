#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "event_groups.h"

EventGroupHandle_t xEventGroup;

#define BIT_TASK1_DONE (1 << 0)
#define BIT_TASK2_DONE (1 << 1)
#define BIT_ALL_TASKS_DONE (BIT_TASK1_DONE | BIT_TASK2_DONE)

void vTask1(void *pvParameters){
    while (1){
        printf("Task1: doing work...\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
        printf("Task1: setting BIT_TASK1_DONE\n");
        xEventGroupSetBits(xEventGroup, BIT_TASK1_DONE);
    }
}

void vTask2(void *pvParameters){
    while (1){
        printf("Task2: doing work...\n");
        vTaskDelay(pdMS_TO_TICKS(1500));
        printf("Task2: setting BIT_TASK2_DONE\n");
        xEventGroupSetBits(xEventGroup, BIT_TASK2_DONE);
    }
}

void vTaskSync(void *pvParameters){
    while (1){
        printf("SyncTask: watting for both tasks to complete\n");
        xEventGroupWaitBits(
            xEventGroup,
            BIT_ALL_TASKS_DONE,
            pdTRUE,
            pdTRUE,
            portMAX_DELAY
        );
        printf("SyncTask: all tasks done, proceeding\n");
    }
}

int main(void){
    printf("TaskN: Event Group synchronization demo start\n");

    xEventGroup = xEventGroupCreate();
    if (xEventGroup == NULL){
        printf("Failed to create event group\n");
        return 1;
    }

    xTaskCreate(vTask1, "Task1", 1000, NULL, 1, NULL);
    xTaskCreate(vTask2, "Task2", 1000, NULL, 1, NULL);
    xTaskCreate(vTaskSync, "SyncTask", 1000, NULL, 2, NULL);

    vTaskStartScheduler();

    for(;;);
    return 0;
}

/* Called when static allocation is enabled */
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
                                   StackType_t **ppxIdleTaskStackBuffer,
                                   uint32_t *pulIdleTaskStackSize) {
    static StaticTask_t xIdleTaskTCB;
    static StackType_t uxIdleTaskStack[configMINIMAL_STACK_SIZE];

    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer,
                                     StackType_t **ppxTimerTaskStackBuffer,
                                     uint32_t *pulTimerTaskStackSize) {
    static StaticTask_t xTimerTaskTCB;
    static StackType_t uxTimerTaskStack[configTIMER_TASK_STACK_DEPTH];

    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}

/* 可空實作，但必須存在 */
void vApplicationIdleHook(void) {}
void vApplicationMallocFailedHook(void) {}
void vApplicationTickHook(void) {}
void vApplicationDaemonTaskStartupHook(void) {}
void vAssertCalled(const char * const pcFileName, unsigned long ulLine) {
    printf("Assert failed at %s:%d\n", pcFileName, ulLine);
    fflush(stdout);
    while (1);
}
