#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "event_groups.h"

EventGroupHandle_t xEventGroup;

#define TASK1_BIT (1 << 0)
#define TASK2_BIT (1 << 1)

void vTask1(void *pvParameters){
    printf("Task1: Initializing...\n");
    vTaskDelay(pdMS_TO_TICKS(1000));
    xEventGroupSetBits(xEventGroup, TASK1_BIT);
    printf("Task1: Initialization complete.\n");
    vTaskDelete(NULL);
}

void vTask2(void *pvParameters){
    printf("Task2: Initializing...\n");
    vTaskDelay(pdMS_TO_TICKS(2000));
    xEventGroupSetBits(xEventGroup, TASK2_BIT);
    printf("Task2: Initialization complete.\n");
    vTaskDelete(NULL);    
}

void vTask3(void *pvParameters){
    printf("Task3: Watting for system ready...\n");
    xEventGroupWaitBits(
        xEventGroup,
        TASK1_BIT | TASK2_BIT,
        pdTRUE,
        pdTRUE,
        portMAX_DELAY
    );
    printf("Task3: All initialization done. Running...\n");
    while (1){
        vTaskDelay(pdMS_TO_TICKS(1000));
        printf("Task3: Working...\n");
    }
}
int main(void){
    xEventGroup = xEventGroupCreate();
    if (xEventGroup == NULL){
        printf("Failed to create Event Group.\n");
        return 1;
    }

    xTaskCreate(vTask1, "Task1", 1000, NULL, 1, NULL);
    xTaskCreate(vTask2, "Task2", 1000, NULL, 1, NULL);
    xTaskCreate(vTask3, "Task3", 1000, NULL, 1, NULL);

    vTaskStartScheduler();

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
