# TaskL - 使用 FreeRTOS Timer Callback 控制任務

本學習示範如何使用 FreeRTOS 軟體定時器 (Software Timer) 的 callback 函式來通知另一個任務執行。

---

## 功能說明

- 建立一個週期性 Timer（每 2 秒）
- 當 Timer callback 觸發時，使用 `xTaskNotifyGive()` 通知任務
- 任務透過 `ulTaskNotifyTake()` 等待通知後執行特定操作

---

## 函式說明

### `vTaskWaitForNotification(void *pvParameters)`
- 任務函式，進入無限迴圈等待來自定時器 callback 的通知。
- 使用 `ulTaskNotifyTake(pdTRUE, portMAX_DELAY)` 阻塞直到接收到通知。
- 接收到通知後印出訊息。

### `vTimerCallback(TimerHandle_t xTimer)`
- 軟體定時器的 callback 函式。
- 每次 Timer 到期時呼叫，利用 `xTaskNotifyGive()` 喚醒指定任務。

### `main(void)`
- 建立任務與定時器，啟動排程器。
- Timer 為週期性，初始化後會自動每 2 秒觸發一次。

---

