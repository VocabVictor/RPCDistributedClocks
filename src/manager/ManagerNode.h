#ifndef MANAGERMAIN_H
#define MANAGERMAIN_H

#include <vector>
#include <string>
#include <unordered_map>
#include "ManagerNode.h"

#if defined(_WIN32) || defined(__CYGWIN__)
#define MANAGER_MAIN __declspec(dllexport)
#else
#define MANAGER_MAIN
#endif


class MANAGER_MAIN ManagerMain {
public:
    explicit ManagerMain(bool dualMode, int port = 1080, int waittime = 5);

    void start();
    void stop();

    void addManager(const std::string& managerAddress,int port);
    void removeManager(const std::string& nodeAddress, int port);
    void monitorManagers(); // 监听管理器节点的状态

private:
    bool _isRunning;
    bool _dualMode;
    int _waittime;
    int _port;
    const std::string _log = "manager.log";
    std::unordered_map<ManagerNode &,int> _managerMap;
    std::vector<ManagerNode> _managers;

    // 处理异常状态的方法，例如转移工作节点
    void handleManagerFailure(const std::string& managerAddress);
    void log(const std::string& message);
};

#endif // MANAGERMAIN_H
