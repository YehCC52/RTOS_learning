# TaskK - 使用 Event Groups 實作多任務同步 (FreeRTOS Event Group Synchronization)

本練習學習如何使用 **FreeRTOS Event Groups** 讓多個任務使用事件位元 (Event Bits) 進行同步。  
Event Groups 可視為「多位元旗標」，每個 bit 可代表不同事件是否已完成。

---

# 1. 使用到的 FreeRTOS Function 詳細解釋

| Function | 功能說明 |
|---------|----------|
| **xEventGroupCreate()** | 建立 Event Group，回傳 `EventGroupHandle_t` 供後續任務使用。 |
| **xEventGroupSetBits(xEventGroup, bits)** | 將 Event Group 中的指定 bit(s) 設為 1，用來告知「事件已完成」。 |
| **xEventGroupWaitBits(xEventGroup, bitsToWaitFor, clearOnExit, waitForAllBits, timeout)** | 讓任務等待某些 bit(s) 被設定完成，具備同步作用。 |
| **vTaskDelay(ms)** | 讓任務進入 Block 狀態指定毫秒，模擬初始化/工作流程。 |
| **xTaskCreate()** | 建立任務並加入排程。 |
| **vTaskStartScheduler()** | 啟動 FreeRTOS 排程器。 |

---

# 2. Event Bits 定義

```c
#define TASK1_BIT   (1 << 0)   // bit0
#define TASK2_BIT   (1 << 1)   // bit1
