#ifndef MANAGERMAIN_H
#define MANAGERMAIN_H

#if defined(_WIN32) || defined(__CYGWIN__)
#define MANAGER_MAIN __declspec(dllexport)
#else
#define MANAGER_MAIN
#endif

#if defined(_WIN32) || defined(__CYGWIN__)
#define MANAGER_SERVICE_IMPL __declspec(dllexport)
#else
#define MANAGER_SERVICE_IMPL
#endif

#if defined(_WIN32) || defined(__CYGWIN__)
#define RPC_SERVER __declspec(dllexport)
#else
#define RPC_SERVER
#endif

#include <string>
#include <vector>
#include <functional>
#include <unordered_map>
#include "../common/RpcChannel.h"

class RPC_SERVER RpcServer {
public:
    explicit RpcServer(int port);
    ~RpcServer();

    [[noreturn]] void start() const;
    void registerService(const std::string& serviceName, std::function<void(RpcChannel&)> handler);
    bool checkRpcConnection(const std::string& targetAddress, int targetPort);

private:
    int port_;
    std::unordered_map<std::string, std::function<void(RpcChannel&)>> services;
    void handleClient(RpcChannel channel) const;

};

class MANAGER_MAIN ManagerNode {
public:
    explicit ManagerNode(int port = 1080);

    void start();

    void addWorker(const std::string& managerAddress,int port);
    // 处理异常状态的方法，例如转移工作节点
    void removeWorker(const std::string& nodeAddress, int port);
    void monitorWorkers();
    void log(const std::string& message);
    void registerServicesToRpcServer();
    std::vector<std::pair<std::string,int>> getWorkers() const;

private:
    int _port;
    RpcServer _rpcServer;
    const std::string _logfile = "manager.log";
    std::vector<std::pair<std::string,int>> _workers;
};

class MANAGER_SERVICE_IMPL ManagerServiceImpl {
public:
    explicit ManagerServiceImpl(ManagerNode *pNode);

    void handleTimeService(RpcChannel& clientRpcChannel);
    void handleDateService(RpcChannel& clientRpcChannel);
    void handleAddWorker(RpcChannel& clientRpcChannel);
    void handleRemoveWorker(RpcChannel& clientRpcChannel);
    void handleMonitorWorkers(RpcChannel& clientRpcChannel);

    const std::unordered_map<std::string, std::function<void(RpcChannel&)>>& getServices() const {
        return serviceHandlers;
    }

private:
    std::unordered_map<std::string, std::function<void(RpcChannel&)>> serviceHandlers{};
    ManagerNode* _managerNode;
};



#endif // MANAGERMAIN_H
