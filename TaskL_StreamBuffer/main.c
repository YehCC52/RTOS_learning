#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include <string.h>
#include "stream_buffer.h"

StreamBufferHandle_t xStreamBuffer;

#define STREAM_BUFFER_SIZE 50
#define TRIGGER_LEVEL 1

void vProducerTask(void *pvParameters){
    const char *msg = "HelloRTOS";
    while (1){
        size_t xBytesSent = xStreamBufferSend(
            xStreamBuffer,
            (void *)msg,
            strlen(msg),
            portMAX_DELAY
        );

        printf("Producer sent %zu bytes:%s\n", xBytesSent, msg);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void vConsumerTask(void *pvParameters){
    char rxBuffer[20];

    while (1){
        memset(rxBuffer, 0, sizeof(rxBuffer));
        
        size_t xReceived = xStreamBufferReceive(
            xStreamBuffer,
            (void *)rxBuffer,
            sizeof(rxBuffer),
            portMAX_DELAY
        );

        printf("Consumer received %zu bytes: %s\n", xReceived, rxBuffer);
    }
}

int main(void){
    xStreamBuffer = xStreamBufferCreate(STREAM_BUFFER_SIZE, TRIGGER_LEVEL);
    if (xStreamBuffer == NULL){
        printf("Failed to create Stream Buffer.\n");
        return 1;
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
