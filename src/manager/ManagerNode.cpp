#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <thread>
#include <algorithm>
#include "ManagerNode.h"

ManagerNode::ManagerNode(int port) : _port(port), _rpcServer(port) {}

void ManagerNode::start() {
    registerServicesToRpcServer();
    _rpcServer.start(); // 启动RPC服务器
}

void ManagerNode::registerServicesToRpcServer() {
    // 在这里注册 ManagerServiceImpl 的服务到 RpcServer
    ManagerServiceImpl serviceImpl(this);
    for(const auto& serviceHandler : serviceImpl.getServices()){
        _rpcServer.registerService(serviceHandler.first,serviceHandler.second);
    }
}

void ManagerNode::addWorker(const std::string& nodeAddress, int port) {
    // 添加管理器逻辑
    _workers.emplace_back(nodeAddress,port);
}

void ManagerNode::removeWorker(const std::string& nodeAddress, int port) {

    // 使用 std::find 查找要移除的工作节点
    auto it = std::find(_workers.begin(), _workers.end(), std::make_pair(nodeAddress, port));

    // 检查是否找到工作节点
    if (it != _workers.end()) {
        // 找到节点，从向量中移除它
        _workers.erase(it);
        // 可以添加其他逻辑，如通知成功移除等
        log("Worker removed");
    } else {
        // 没有找到节点
        log("Node not found");
    }

}


void ManagerNode::monitorWorkers() {
    std::vector<std::pair<std::string, int>> disconnectedWorkers;

    // 检查每个管理器的状态
    for (const auto& worker : _workers) {
        bool isConnected = _rpcServer.checkRpcConnection(worker.first, worker.second);
        if (!isConnected) {
            // 如果发生异常，则将该管理器添加到待移除列表
            disconnectedWorkers.push_back(worker);
        }
    }

    // 移除所有断开连接的工作节点
    for (const auto& worker : disconnectedWorkers) {
        removeWorker(worker.first, worker.second);
    }

    if (_workers.empty()) {
        log("No workers are running");
    } else {
        log("All workers are running");
    }
}



void ManagerNode::log(const std::string& message) {
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    std::tm tm{};
    std::stringstream ss;

    #ifdef _MSC_VER
        localtime_s(&tm, &now_c);
    #else
        localtime_r(&now_c, &tm);
    #endif

    ss << std::put_time(&tm, "%Y-%m-%d %X") << " - " << message;

    // 输出到文件
    std::ofstream logFile(_logfile, std::ios::app);
    if (logFile.is_open()) {
        logFile << "Manager Log: " << ss.str() << std::endl;
    } else {
        // 可以在这里处理文件打开失败的情况
        // 记录到备用日志或通知用户
        std::cerr << "Manager Log: " << ss.str() << std::endl;
    }
}

std::vector<std::pair<std::string,int>> ManagerNode::getWorkers() const {
    return _workers;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ManagerServiceImpl::ManagerServiceImpl(ManagerNode *pNode) {
    serviceHandlers["time"] = [this](RpcChannel& clientRpcChannel) { handleTimeService(clientRpcChannel); };
    serviceHandlers["date"] = [this](RpcChannel& clientRpcChannel) { handleDateService(clientRpcChannel); };
    serviceHandlers["addworker"] = [this](RpcChannel& clientRpcChannel) { this->handleAddWorker(clientRpcChannel); };
    serviceHandlers["removeworker"] = [this](RpcChannel& clientRpcChannel) { this->handleRemoveWorker(clientRpcChannel); };
    serviceHandlers["monitorworkers"] = [this](RpcChannel& clientRpcChannel) { this->handleMonitorWorkers(clientRpcChannel); };
    _managerNode = pNode;
}

void ManagerServiceImpl::handleTimeService(RpcChannel& clientRpcChannel) {
    // 接收请求
    RpcProtocol::RpcRequest request = clientRpcChannel.receiveRequest();

    // 构造响应
    RpcProtocol::RpcResponse response;
    response.success = true;
    response.data = "data: 2023-10-15";

    // 发送响应
    clientRpcChannel.sendResponse(response);
}

void ManagerServiceImpl::handleDateService(RpcChannel& clientRpcChannel) {
}

void ManagerServiceImpl::handleAddWorker(RpcChannel& clientRpcChannel) {
}

void ManagerServiceImpl::handleRemoveWorker(RpcChannel& clientRpcChannel) {
}

void ManagerServiceImpl::handleMonitorWorkers(RpcChannel& clientRpcChannel) {
}


//////////////////////////////////////////////////////////////////////////////


RpcServer::RpcServer(int port) : port_(port) {}

RpcServer::~RpcServer() = default;

void RpcServer::registerService(const std::string& serviceName, std::function<void(RpcChannel&)> handler) {
    services[serviceName] = std::move(handler);
}

void RpcServer::handleClient(RpcChannel channel) const {
    // 接收请求
    RpcProtocol::RpcRequest request = channel.receiveRequest();

    // 打印请求体信息
    std::cout << "Received request for service: " << request.serviceName << std::endl;
    std::cout << "Request data: " << request.data << std::endl;

    // 查找并调用相应的服务处理函数
    auto it = services.find(request.serviceName);
    if (it != services.end()) {
        // 调用服务处理函数
        it->second(channel);
    } else {
        // 打印错误信息，如果找不到相应的服务
        std::cerr << "Service not found: " << request.serviceName << std::endl;

        // 打印可用的服务列表
        std::cerr << "Available services:" << std::endl;
        for (const auto& service : services) {
            std::cerr << " - " << service.first << std::endl;
        }
    }

    // 断开连接
    channel.disconnect();
}


bool RpcServer::checkRpcConnection(const std::string& targetAddress, int targetPort) {
    return true;
}

void RpcServer::start() const {
    std::cout << "Server started, waiting for connections on port " << port_ << std::endl;

    RpcChannel rpc_server_channel(port_); // 创建用于接受连接的 RpcChannel
    rpc_server_channel.listenAndAccept([this](RpcChannel channel) { handleClient(channel); }); // 监听连接并处理客户端
}