# Task H - 使用 Task Notification 實作任務同步 (取代 Semaphore 的輕量替代方案)

## 任務說明

本範例學習如何使用 FreeRTOS 提供的輕量級同步機制 **Task Notification**，在兩個任務間進行事件觸發與等待。

這個機制可以在不額外使用 semaphore、queue 或其他 RTOS 資源的情況下，完成類似同步行為，且效能更高。

---

## 學習目標

- 了解什麼是 Task Notification，以及與 semaphore 的差異。
- 學習使用 `xTaskNotifyGive()` 來通知任務。
- 使用 `ulTaskNotifyTake()` 讓任務等待特定事件發生。
- 強化任務間的事件傳遞觀念。

---

## 核心概念

| API | 說明 |
|-----|------|
| `xTaskNotifyGive()` | 向目標任務發送一個「通知」訊號 |
| `ulTaskNotifyTake(clearOnExit, timeout)` | 等待一個通知，類似於 `xSemaphoreTake()` |
| `pdTRUE` | 表示接收到通知後會自動清除計數值 |
| `portMAX_DELAY` | 任務會無限期等待直到接收到通知 |

Task Notification 是內建在 Task Control Block 中的位元欄位，比 Semaphore 更省資源與高效。

---

## 任務架構說明

- **NotifierTask**：每 2 秒呼叫一次 `xTaskNotifyGive()`，通知 HandlerTask。
- **HandlerTask**：透過 `ulTaskNotifyTake()` 阻塞等待通知，一旦收到通知便執行對應任務。

```text
[NotifierTask] ---> (Task Notification) ---> [HandlerTask]
