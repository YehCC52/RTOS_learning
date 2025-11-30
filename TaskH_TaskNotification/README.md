# Task N - 使用 Event Group 同步多任務狀態

## 任務說明

本範例學習如何透過 **FreeRTOS 的 Event Group** 機制，讓多個任務完成特定工作後再喚醒另一任務執行。這是一種常見的同步邏輯，例如：等待多個感測器完成初始化、或等多個子任務結束後再整合處理。

Event Group 提供 24 個可設定的事件位元 (bits)，讓任務之間可依條件進行同步與通訊。

---

## 學習目標

- 學會使用 `xEventGroupSetBits()` 來設定特定事件位元。
- 使用 `xEventGroupWaitBits()` 讓任務等待多個事件完成。
- 掌握「多任務完成 → 同步執行下一步」的典型設計模式。
- 熟悉 FreeRTOS Event Group 的 AND / OR 條件等待邏輯。

---

## 核心概念

| API | 說明 |
|-----|------|
| `xEventGroupCreate()` | 建立一個事件群組 (event group) |
| `xEventGroupSetBits(group, bits)` | 將指定的位元設為 1（代表某事件已完成） |
| `xEventGroupWaitBits(group, bitsToWaitFor, clearOnExit, waitForAllBits, timeout)` | 阻塞任務直到事件發生 |
| `pdTRUE` | 常用參數，表示條件滿足後自動清除相應位元 |
| `portMAX_DELAY` | 無限期等待事件發生 |

Event Group 本質上是 24-bit 的共享變數，適合條件式同步，但不適合傳送資料內容（適合使用 queue）。

---

## 任務架構說明

- **Task1**：模擬第一個任務完成，設定 `BIT_TASK1_DONE`。
- **Task2**：模擬第二個任務完成，設定 `BIT_TASK2_DONE`。
- **SyncTask**：透過 `xEventGroupWaitBits()` 等待 Task1 與 Task2 都完成後再繼續執行。

