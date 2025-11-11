#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "queue.h"

QueueHandle_t xQueue;

void vProducerTask(void *pvParameters){
    int i = 0;
    while (1){
        printf("Producer sending: %d\n", i);
        xQueueSend(xQueue, &i, portMAX_DELAY);
        i++;
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void vConsumerTask(void *pvParameters){
    int receivedValue;
    while (1) {
        if (xQueueReceive(xQueue, &receivedValue, portMAX_DELAY) == pdPASS){
            printf("Consuner received: %d\n", receivedValue);
        }
    }
}

int main(void){
    xQueue = xQueueCreate(5, sizeof(int));

    if (xQueue == NULL){
        printf("Failed to create queue.\n");
        while (1);
    }

    xTaskCreate(vProducerTask, "Producer", 1000, NULL, 1, NULL);
    xTaskCreate(vConsumerTask, "Consumer", 1000, NULL, 1, NULL);

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
