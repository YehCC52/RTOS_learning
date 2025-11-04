# Task F - 使用 Binary Semaphore 模擬 ISR 中斷觸發任務

## 練習目標

模擬「中斷服務程序（ISR）」觸發 RTOS 任務的情境，透過 Binary Semaphore（雙值訊號量）來達成 ISR 與任務間的同步與解耦。

---

## 學習重點

| 主題 | 說明 |
|------|------|
| Binary Semaphore | 一種只能為 0 或 1 的信號量，適合事件觸發 |
| xSemaphoreTake() | 任務阻塞等待 Semaphore |
| xSemaphoreGiveFromISR() | 在模擬中斷內釋放 Semaphore |
| ISR 與任務解耦 | 中斷不直接執行任務邏輯，只觸發事件，由任務完成後續處理 |

---

## 檔案說明

| 檔案名稱 | 功能 |
|----------|------|
| `main.c` | 建立一個模擬中斷與任務的雙任務架構，使用 Binary Semaphore 同步 |
| `Makefile` | 編譯設定，產出可執行檔 |
| `FreeRTOSConfig.h` | FreeRTOS 系統設定參數 |

---

## 任務設計

### ISR_SimulatorTask

- 週期性（每 2 秒）模擬一次 ISR（中斷觸發）
- 使用 `xSemaphoreGiveFromISR()` 釋放 Binary Semaphore

### InterruptHandlerTask

- 使用 `xSemaphoreTake()` 長時間等待 ISR 訊號
- 一旦接收到訊號，就執行「中斷任務邏輯」

---

