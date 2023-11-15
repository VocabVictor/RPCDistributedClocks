#include "WorkerNode.h"

WorkerNode::WorkerNode(const std::string& nodeAddress, int nodePort)
        : nodeAddress_(nodeAddress), nodePort_(nodePort), rpcClient_(nodePort) {
}


void WorkerNode::connectToManager(const std::string& managerAddress, int managerPort) {
    rpcClient_.connect(managerAddress, managerPort);

    // 构造一个请求来注册工作节点
    RpcProtocol::RpcRequest request;
    request.serviceName = "addworker";
    request.data = "Address: " + nodeAddress_ + "; Port: " + std::to_string(nodePort_);

    // 发送请求
    RpcProtocol::RpcResponse response = rpcClient_.sendRequest(request);

    // 处理响应
    // 这可能包括检查是否成功注册，以及接收任何来自管理器的指令
    managerAddress_ = managerAddress;
    managerPort_ = managerPort;
}

void WorkerNode::disconnectFromManager() {
    rpcClient_.disconnect();
    // 可能还需要进行一些清理操作
}

void WorkerNode::performTask() {
//    // 从 Manager 节点获取任务
//    RpcProtocol::RpcRequest request;
//    request.set_type(RpcProtocol::RpcRequest::REQUEST_TASK);
//    RpcProtocol::RpcResponse response = rpcClient_.sendRequest(request);
//    if (response.type() == RpcProtocol::RpcResponse::NO_TASK) {
//        // 没有任务可执行
//        return;
//    }
//
//    // 执行任务
//    std::string task = response.task();
//    std::cout << "Performing task: " << task << std::endl;
//
//    // 将任务结果发送给 Manager 节点
//    request.set_type(RpcProtocol::RpcRequest::REPORT_RESULT);
//    request.set_task(task);
//    request.set_result("Task result");
//    rpcClient_.sendRequest(request);
}