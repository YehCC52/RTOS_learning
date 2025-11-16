# Task L - 使用 Stream Buffer 實作連續資料串流傳輸

本練習 FreeRTOS **Stream Buffer**，適用於 UART 連續資料接收、Sensor streaming、音訊資料等用途。

---

# 1. 使用到的 FreeRTOS Functions

| Function | 說明 |
|---------|------|
| **xStreamBufferCreate(size, triggerLevel)** | 建立 Stream Buffer，size=總容量，triggerLevel=喚醒 Consumer 的最小 bytes 數 |
| **xStreamBufferSend(handle, data, length, timeout)** | 向 Stream Buffer 寫入資料（Producer 寫入資料來源端） |
| **xStreamBufferReceive(handle, buffer, length, timeout)** | 從 Stream Buffer 讀取資料（Consumer 端） |
| **vTaskDelay(ms)** | Block 任務指定毫秒 |
| **xTaskCreate()** | 建立任務 |
| **vTaskStartScheduler()** | 啟動 RTOS 排程器 |

---

