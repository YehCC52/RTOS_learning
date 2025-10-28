# Task D - 使用 Mutex 實作任務同步與共享資源保護

##  練習目標
透過 FreeRTOS 提供的 `Semaphore` 機制（實際上為 Mutex 型態）來達成任務之間對共享資源的同步控制，避免同時存取造成錯誤或資源衝突。

---

##  學習重點

| 主題                    | 說明                                                   |
|-------------------------|--------------------------------------------------------|
| `xSemaphoreCreateMutex()` | 建立一個 Mutex（互斥鎖）來保護共享資源                |
| `xSemaphoreTake()`      | 任務在進入臨界區（critical section）前需取得鎖         |
| `xSemaphoreGive()`      | 任務在離開臨界區後釋放鎖，讓其他任務可以繼續存取資源   |
| `portMAX_DELAY`         | 表示任務會一直等待直到成功取得鎖                     |

---

##  檔案內容

- `main.c`：包含兩個模擬寫入共享資源的任務（Writer 1 & Writer 2）
- `FreeRTOSConfig.h`：RTOS 設定參數
- `Makefile`：編譯參數與檔案設定

---

##  任務設計

### Writer 1 與 Writer 2
- 兩個任務會試圖存取同一資源（透過 printf 模擬）
- 為了避免同時存取，我們使用 Mutex 控制「同一時間只允許一個任務執行臨界區程式碼」

---

