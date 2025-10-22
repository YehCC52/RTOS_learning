# Task A & Task B 實作記錄

## 目標

- 建立單一任務：Task A 每秒印出訊息
- 建立第二任務：Task B 每 0.5 秒印出訊息
- 練習 FreeRTOS 任務排程與時間延遲

## 任務代碼摘要

xTaskCreate(vTaskA, "TaskA", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
xTaskCreate(vTaskB, "TaskB", configMINIMAL_STACK_SIZE, NULL, 1, NULL);i
