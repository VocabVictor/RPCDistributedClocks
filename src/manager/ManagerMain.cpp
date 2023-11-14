#include "ManagerMain.h"

ManagerMain::ManagerMain() : isRunning(false) {
    // 构造函数初始化
}

void ManagerMain::start() {
    // 启动管理器的逻辑
    isRunning = true;
}

MANAGER_MAIN void ManagerMain::stop() {
    // 停止管理器的逻辑
    isRunning = false;
}
