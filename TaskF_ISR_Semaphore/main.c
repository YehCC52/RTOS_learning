#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "semphr.h"

SemaphoreHandle_t xBinarySemaphore;

void ISR_SimulatorTask(void *pvParameters){
    while (1){
        vTaskDelay(pdMS_TO_TICKS(2000));
        printf("Simulated ISR triggered!\n");

        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        xSemaphoreGiveFromISR(xBinarySemaphore, &xHigherPriorityTaskWoken);
    }
}

void InterruptHandlerTask(void *pvParameters){
    while (1){
        if (xSemaphoreTake(xBinarySemaphore, portMAX_DELAY) == pdTRUE){
            printf("Interrupt Handler Task Activated!\n");
        }
    }
}

int main(void){
    xBinarySemaphore = xSemaphoreCreateBinary();
    if (xBinarySemaphore == NULL){
        printf("Failed to create binary semaphore\n");
        return 1;
    }

    xTaskCreate(ISR_SimulatorTask, "ISR_Sim", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    xTaskCreate(InterruptHandlerTask, "Handler", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

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
