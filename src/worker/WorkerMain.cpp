#include "WorkerMain.h"
#include <iostream>

// 实现 WorkerMain 构造函数
WorkerMain::WorkerMain() : isRunning(false) {}

// 启动 Worker
void WorkerMain::start() {
    if (!isRunning) {
        std::cout << "Worker started." << std::endl;
        isRunning = true;
    }
}

// 停止 Worker
void WorkerMain::stop() {
    if (isRunning) {
        std::cout << "Worker stopped." << std::endl;
        isRunning = false;
    }
}

// 执行任务
void WorkerMain::executeTask(const std::string& task) {
    if (isRunning) {
        std::cout << "Executing task: " << task << std::endl;
        // 在这里执行任务的实际逻辑
    } else {
        std::cout << "Worker is not running. Cannot execute task." << std::endl;
    }
}
