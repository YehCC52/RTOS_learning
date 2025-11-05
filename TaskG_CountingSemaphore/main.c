#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "semphr.h"

SemaphoreHandle_t xCountingSemaphore;

void vTask(void *pvParameters){
    char *taskName = (char *)pvParameters;
    while (1){
        if (xSemaphoreTake(xCountingSemaphore, portMAX_DELAY) == pdPASS){
            printf("%s got a resource\n", taskName);
            vTaskDelay(pdMS_TO_TICKS(1000));
            printf("%s released a resource\n", taskName);
            xSemaphoreGive(xCountingSemaphore);
            vTaskDelay(pdMS_TO_TICKS(500));
        }
    }
}

int main(void){
    xCountingSemaphore = xSemaphoreCreateCounting(2, 2);
    if (xCountingSemaphore == NULL){
        printf("Failed to create counting semaphore\n");
        while (1);
    }

    xTaskCreate(vTask, "Task 1", 1000, "Task 1", 1, NULL);
    xTaskCreate(vTask, "Task 2", 1000, "Task 2", 1, NULL);
    xTaskCreate(vTask, "Task 3", 1000, "Task 3", 1, NULL);

    vTaskStartScheduler();

    while (1);
    
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
