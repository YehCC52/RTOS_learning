#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "timers.h"

#define TIMER_PERIOD_MS pdMS_TO_TICKS(2000)

TaskHandle_t xNotifyTaskHandle = NULL;
TimerHandle_t xTimer = NULL;

void vTaskWaitForNotification(void *pvParameters){
    for(;;){
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        printf("TaskL: Notification received from timer callback!\n");
    }
}

void vTimerCallback(TimerHandle_t xTimer){
    printf("Timer Callback fired!\n");
    xTaskNotifyGive(xNotifyTaskHandle);
}

int main(void){
    printf("System Start\n");

    xTaskCreate(vTaskWaitForNotification, "NotifyTask", 1000, NULL, 1, &xNotifyTaskHandle);
    
    xTimer = xTimerCreate("Timer", TIMER_PERIOD_MS, pdTRUE, NULL, vTimerCallback);
    if (xTimer != NULL){
        xTimerStart(xTimer, 0);
    }
   
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
