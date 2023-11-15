#ifndef WORKERNODE_H
#define WORKERNODE_H

// 定义动态库导出宏
#if defined(_WIN32) || defined(__CYGWIN__)
#define WORKER_NODE __declspec(dllexport)
#else
#define WORKER_NODE
#endif

#include <string>
#include "RpcClient.h"
#include "../common/RpcProtocol.h"

class WORKER_NODE WorkerNode {
public:
    WorkerNode(const std::string& nodeAddress,int nodePort);

    void connectToManager(const std::string &managerAddress, int managerPort);
    void disconnectFromManager();

    void performTask();

private:
    RpcClient rpcClient_;
    std::string managerAddress_;
    int managerPort_;
    // 其他与 WorkerNode 相关的成员
    std::string nodeAddress_;
    int nodePort_;
};


#endif // WORKERNODE_H
