#include "ManagerMain.h"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <thread>
#include <algorithm>
// 包含其他必要的头文件

ManagerMain::ManagerMain(bool dualMode, int port, int waittime)
{
    _isRunning = false;
    _dualMode = dualMode;
    _port = port;
    _waittime = waittime;
}

void ManagerMain::start() {
    _isRunning = true;
    // 启动逻辑，可能包括启动监控管理器的线程
    if( !_dualMode ){
        monitorManagers();
    }else{
        // 启动管理器逻辑
        addManager("127.0.0.1",_port);
    }
}

void ManagerMain::stop() {
    _isRunning = false;
    // 停止逻辑
}

void ManagerMain::addManager(const std::string& nodeAddress,int port) {
    // 添加管理器逻辑
    ManagerNode node(nodeAddress,port);
    _managers.emplace_back(node);
}

void ManagerMain::removeManager(const std::string& nodeAddress, int port) {

}


void ManagerMain::monitorManagers() {
    bool exceptionOccurred;
    while (_isRunning) {
        exceptionOccurred = false;
        // 定期检查每个管理器的状态
        for (ManagerNode manager : _managers) {
            // 如果发现管理器异常
             if ( !manager.checkRpcConnection("127.0.0.1",_port) ) {
                handleManagerFailure(manager);
                 exceptionOccurred = true;
             }
        }

        // 每5秒检查一次
        std::this_thread::sleep_for(std::chrono::seconds(_waittime));
        if( !exceptionOccurred ){
            log("All managers are running normally.");
        }
    }
}

void ManagerMain::handleManagerFailure(const std::string& managerAddress) {
    // 处理管理器失败的逻辑，如转移其下属工作节点
    // ...
}

void ManagerMain::log(const std::string& message) {
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_c), "%Y-%m-%d %X") << " - " << message;

    // 输出到控制台
    std::cout << "Log: " << ss.str() << std::endl;

    // 输出到文件
    std::ofstream logFile(_log, std::ios::app);
    logFile << "Log: " << ss.str() << std::endl;
}