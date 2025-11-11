# Task I - 使用 Queue 實作任務間資料傳遞（Inter-task Communication）

## 任務說明

本學習展示如何透過 **FreeRTOS 的 Queue 機制**，在兩個任務之間進行整數資料的安全傳遞。這是 RTOS 中常見的任務間通訊方法之一，能夠有效避免 race condition 並提升系統模組化設計能力。

---

## 學習目標

- 熟悉 `xQueueCreate()` 建立資料佇列
- 使用 `xQueueSend()` 傳送資料
- 使用 `xQueueReceive()` 接收資料
- 模擬 Producer / Consumer 結構設計

---

## 核心概念

| 函式 | 說明 |
|------|------|
| `xQueueCreate(length, itemSize)` | 建立一個可儲存固定數量項目的 queue |
| `xQueueSend(queue, itemPtr, timeout)` | 傳送資料至 queue（若 queue 滿則等待） |
| `xQueueReceive(queue, itemPtr, timeout)` | 接收 queue 中資料（若 queue 空則等待） |

Queue 是 **任務間傳遞資料的安全機制**，具 FIFO 行為與 thread-safe 特性。

---

