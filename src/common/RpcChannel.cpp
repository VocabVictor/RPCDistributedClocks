//
// Created by teenager on 2023/11/15.
//

#include <thread>
#include <iostream>
#include "RpcChannel.h"

RpcChannel::RpcChannel(int port) {
    port_ = port;
    // 创建 Socket
    socket_.create();
    // 绑定 Socket
    socket_.bind(port_);
}

RpcChannel::RpcChannel(RpcSocket& socket) {
    socket_ = socket;
}

RpcChannel::~RpcChannel() {
    disconnect();
}

void RpcChannel::connect(const std::string& address, int port) {
    // 使用 Socket 建立连接
    socket_.create();
    socket_.connect(address,port);
}

void RpcChannel::disconnect() {
    // 关闭连接
    socket_.close();
}

RpcProtocol::RpcResponse RpcChannel::sendRequest(const RpcProtocol::RpcRequest& request) {
    // 序列化请求
    std::string serializedRequest = RpcProtocol::serialize(request);
    socket_.sendData(serializedRequest.c_str(), serializedRequest.size(), 0);

    // 接收响应
    char buffer[1024];
    socket_.receiveData(buffer, sizeof(buffer), 0);

    disconnect();

    // 反序列化响应
    return RpcProtocol::deserializeResponse(std::string(buffer));
}

RpcProtocol::RpcRequest RpcChannel::receiveRequest() {
    // 接收请求
    char buffer[1024] = {0}; // 初始化所有元素为 0
    int receivedBytes = socket_.receiveData(buffer, sizeof(buffer) - 1, 0); // 保留一个字符的空间用于空字符

    // 检查是否成功接收到数据
    if (receivedBytes <= 0) {
        // 处理错误或空数据的情况
        std::cout << "Error receiving data." << std::endl;
        return {}; // 返回一个空的或错误的 RpcRequest 对象
    }

    // 反序列化请求
    return RpcProtocol::deserializeRequest(std::string(buffer));
}


void RpcChannel::sendResponse(const RpcProtocol::RpcResponse& response) {
    // 序列化响应
    std::string serializedResponse = RpcProtocol::serialize(response);
    socket_.sendData(serializedResponse.c_str(), serializedResponse.size(), 0);
}


[[noreturn]] void RpcChannel::listenAndAccept(std::function<void(RpcChannel)> clientHandler) {
    // 开始监听端口
    socket_.listen();

    while (true) {
        // 接受传入连接
        RpcSocket newSocket = socket_.accept();

        // 检查 newSocket 是否有效
        if (newSocket.isValid()) {
            // 为每个接受的连接创建新的 RpcChannel 实例
            RpcChannel newChannel(newSocket); // 假设 RpcChannel 支持移动构造

            // 在新线程中处理这个连接
            std::thread([clientHandler, channel = newChannel]() mutable {
                clientHandler(channel);
            }).detach();
        }
    }
}
