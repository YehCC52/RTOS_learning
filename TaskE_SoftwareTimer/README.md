# Task E - 使用 Software Timer（軟體定時器）進行週期性任務

## 練習目標

本練習學習如何使用 FreeRTOS 提供的 **Software Timer（軟體定時器）**，以非任務（Task）方式實作週期性邏輯，達成省資源、可控的事件觸發。

---

## 學習重點

| 主題                        | 說明                                                                 |
|-----------------------------|----------------------------------------------------------------------|
| `xTimerCreate()`            | 建立一個軟體定時器物件                                               |
| `xTimerStart()`             | 啟動定時器，開始計時與週期性觸發                                     |
| `vTimerCallback()`          | 當定時器時間到時，自動呼叫的函式（相當於「事件處理器」）             |
| `pdMS_TO_TICKS(ms)`         | 將毫秒轉為 FreeRTOS 時脈單位（tick）                                 |
| `vTaskStartScheduler()`     | 啟動 RTOS 核心，進入排程與定時控制                                    |

---

## 檔案內容

| 檔案名稱         | 用途說明                       |
|------------------|--------------------------------|
| `main.c`         | 主程式，包含軟體定時器設定與回呼函式 |
| `FreeRTOSConfig.h` | RTOS 核心參數設定              |
| `Makefile`       | 編譯設定                       |

---

##  程式邏輯設計

- 使用 `xTimerCreate()` 建立一個週期為 1 秒的 timer
- 當 timer 超時時，自動觸發 `vTimerCallback()` 印出訊息
- 使用 `xTimerStart()` 啟動 timer
- `main()` 中僅需啟動 scheduler 即可，無需額外任務

---

