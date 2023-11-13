#include "RpcServer.h"
#include <iostream>

// 构造函数
RpcServer::RpcServer(asio::io_context& io_context, int port)
        : io_context_(io_context),
          acceptor_(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)),
          socket_(io_context) {
}

// 启动服务器，开始监听连接
void RpcServer::start() {
    doAccept();
}

// 异步接受新的连接
void RpcServer::doAccept() {
    acceptor_.async_accept(socket_, [this](std::error_code ec) {
        if (!ec) {
            // 成功接受新连接
            std::cout << "New connection accepted" << std::endl;
            // 可以在这里调用处理连接的函数
            doRead();
        }

        // 继续接受其他连接
        doAccept();
    });
}

// 读取来自客户端的数据
void RpcServer::doRead() {
    // 实现读取数据的逻辑
}

// 发送数据到客户端
void RpcServer::doWrite(const std::string& response) {
    // 实现发送数据的逻辑
}

// 处理接收到的请求
void RpcServer::handleRequest(const std::string& request, std::function<void(const std::string&)> callback) {
    // 实现处理请求的逻辑
}

// 处理来自客户端的连接
void RpcServer::handleAccept(const asio::error_code& error) {
    if (!error) {
        // 成功建立连接
        // 这里可以启动读取操作或其他处理
    } else {
        // 处理错误情况
    }
}

// 处理读取操作的结果
void RpcServer::handleRead(const asio::error_code& error, size_t bytes_transferred) {
    // 处理读取结果
}

// 处理写入操作的结果
void RpcServer::handleWrite(const asio::error_code& error, size_t bytes_transferred) {
    // 处理写入结果
}

// 关闭连接
void RpcServer::closeConnection() {
    // 实现关闭连接的逻辑
}
