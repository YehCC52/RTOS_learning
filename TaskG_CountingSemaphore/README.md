# Task G - 使用 Counting Semaphore 控制共享資源數量

## 任務目標

透過 FreeRTOS 的 Counting Semaphore 實作，模擬多個任務競爭有限資源的情境。此範例學習如何使用 counting semaphore 管理資源池（resource pool），保證同一時間只有固定數量的任務可以存取共享資源。

---

## 使用元件

- `xSemaphoreCreateCounting()`: 建立 Counting Semaphore
- `xSemaphoreTake()`: 嘗試取得資源（減 1）
- `xSemaphoreGive()`: 歸還資源（加 1）
- `vTaskDelay()`: 任務延遲執行

---

## 程式架構

本範例建立三個任務，每個任務執行以下流程：

1. 等待取得資源（Semaphore）
2. 模擬使用資源（1 秒）
3. 歸還資源
4. 稍作休息後再進行下一輪

透過 Counting Semaphore 設定初始值為 `2`，限制同時最多只有兩個任務可取得資源，避免競爭衝突。

---
