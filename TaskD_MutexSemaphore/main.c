#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "semphr.h"

SemaphoreHandle_t xMutex;

void writerTask(void *param){
    const char *name = (const char *)param;
    while(1){
        if (xSemaphoreTake(xMutex, portMAX_DELAY) == pdTRUE){
            printf("%s acquired mutex, writing...\n", name);
            vTaskDelay(pdMS_TO_TICKS(500));
            printf("%s released mutex\n", name);
            xSemaphoreGive(xMutex);
        }
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

int main(void){
    xMutex = xSemaphoreCreateMutex();
    
    if (xMutex == NULL){
        printf("Failed to created mutex.\n");
        return 1;
    }

    xTaskCreate(writerTask, "Writer1", configMINIMAL_STACK_SIZE, "Writer 1", 1, NULL);
    xTaskCreate(writerTask, "Writer2", configMINIMAL_STACK_SIZE, "Writer 2", 1, NULL);

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
