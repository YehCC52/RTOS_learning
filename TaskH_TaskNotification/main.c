#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

TaskHandle_t xHandlerTaskHandle = NULL;

void vNotifierTask(void *pvParameters){
    while (1){
        printf("notifier: Sending task notification\n");
        xTaskNotifyGive(xHandlerTaskHandle);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void vHandlerTask(void *pvParameters){
    while (1){
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        printf("Handler: Received notification and processing task\n");
    }
}

int main(void){
    xTaskCreate(vHandlerTask, "Handler", 1000, NULL, 2, &xHandlerTaskHandle);
    xTaskCreate(vNotifierTask, "Notifier", 1000, NULL, 1, NULL);

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
