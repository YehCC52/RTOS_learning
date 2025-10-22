# RTOS Learning Journey with FreeRTOS

##  目的
練習 FreeRTOS 任務建立與排程，驗證 TaskA 是否能每秒輸出訊息。

##  環境
- macOS M1 / M2
- FreeRTOS 官方 GitHub clone
- 編譯使用 POSIX demo

##  檔案結構
- `main.c`: 建立 Task A 的主程式
- `FreeRTOSConfig.h`: FreeRTOS 組態設定
- `Makefile`: POSIX demo 的編譯檔

##  執行方式
```bash
make clean
make NO_TRACING=1
./build/posix_demo
