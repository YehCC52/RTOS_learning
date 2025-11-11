#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "semphr.h"

SemaphoreHandle_t xMutex;

void vTask1(void *pvParameters){
    while (1){
        if (xSemaphoreTake(xMutex, portMAX_DELAY) == pdTRUE){
            printf("Task1:Accessing shared resource..\n");
            vTaskDelay(pdMS_TO_TICKS(500));
            printf("Task1:Releasing resource.\n");
            xSemaphoreGive(xMutex);
        }
    }
}

void vTask2(void *pvParameters){
    while (1){
        if (xSemaphoreTake(xMutex, portMAX_DELAY) == pdTRUE){
            printf("Task2:Accessing shared resource...\n");
            vTaskDelay(pdMS_TO_TICKS(300));
            printf("Task2:Releasing resource.\n");
            xSemaphoreGive(xMutex);
        }
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

int main(void){
    xMutex = xSemaphoreCreateMutex();
    if (xMutex == NULL){
        printf("Failed to create mutex.\n");
        return 1;
    }

    xTaskCreate(vTask1, "Task1", 1000, NULL, 1, NULL);
    xTaskCreate(vTask2, "Task2", 1000, NULL, 2, NULL);

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
