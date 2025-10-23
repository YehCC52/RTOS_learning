# Task C - 任務之間的 Queue 傳訊練習

##  練習目標
本練習目標是理解 RTOS 任務間的通訊方式，透過 Queue 實作 Producer 與 Consumer 任務模型，讓任務能有系統地交換資料，避免資料競爭或共享變數問題。

---

##  學習重點
- 使用 `xQueueCreate()` 建立一個具有緩衝的佇列
- 使用 `xQueueSend()` 傳送整數資料至 Queue
- 使用 `xQueueReceive()` 由另一任務接收資料
- 理解 Queue 的阻塞行為與同步機制

---

## 主要 API

| 函式名稱          | 功能描述                               |
|------------------|----------------------------------------|
| `xQueueCreate()` | 建立一個佇列（Queue）                  |
| `xQueueSend()`   | 將資料送入佇列                          |
| `xQueueReceive()`| 從佇列中取出資料                        |
| `portMAX_DELAY`  | 表示任務會無限等待直到成功發送或接收資料 |

---

##  檔案內容

- `main.c`: 實作 Producer 與 Consumer 任務邏輯
- `FreeRTOSConfig.h`: RTOS 設定檔
- `Makefile`: 編譯用設定檔

---

##  任務設計

### Producer 任務
- 每秒傳送一個整數（0 → 1 → 2 → ...）到 Queue
- 使用 `vTaskDelay(1000ms)` 控制頻率

### Consumer 任務
- 一旦收到 Queue 資料即輸出
- 使用 `xQueueReceive(..., portMAX_DELAY)` 阻塞等待新資料

---

