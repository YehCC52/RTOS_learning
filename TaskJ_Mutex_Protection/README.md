# Task J - 使用 Mutex 實作臨界區保護（Mutex Protection for Shared Resource）

本練習 FreeRTOS 中的 Mutex（互斥鎖），透過兩個任務共同存取共享變數，模擬臨界區（Critical Section）的保護機制，避免資料競爭與破壞。

---

## 任務目標

- 使用 `xSemaphoreCreateMutex()` 建立 Mutex。
- 使用 `xSemaphoreTake()` 和 `xSemaphoreGive()` 包裹臨界區。
- 讓兩個任務輪流安全地對共享變數進行寫入與輸出。

---

## 程式架構概覽

| 函式名稱           | 功能說明 |
|--------------------|----------|
| `main()`           | 初始化 Mutex、建立任務、啟動排程器 |
| `vTask1()`         | 嘗試取得 Mutex 後更新共享變數，模擬任務1 行為 |
| `vTask2()`         | 嘗試取得 Mutex 後更新共享變數，模擬任務2 行為 |

---

