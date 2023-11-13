#ifndef RPCSERVER_H
#define RPCSERVER_H

#include "../../lib/asio/asio.hpp"
#include <string>
#include <functional>
#include <memory>

// 定义动态库导出宏
#if defined(_WIN32) || defined(__CYGWIN__)
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

class DLL_EXPORT RpcServer {
public:
    // 构造函数
    RpcServer(asio::io_context& io_context, int port);

    // 启动服务器，开始监听连接
    void start();

private:
    asio::io_context& io_context_;               // Asio I/O 上下文
    asio::ip::tcp::acceptor acceptor_;           // 用于接受新连接的 acceptor
    asio::ip::tcp::socket socket_;               // 用于与客户端通信的 socket
    int port_;                                   // 服务器监听的端口
    std::vector<std::shared_ptr<std::thread>> threads_; // 线程池，用于处理请求

    // 异步接受新的连接
    void doAccept();

    // 读取来自客户端的数据
    void doRead();

    // 发送数据到客户端
    void doWrite(const std::string& response);

    // 处理接收到的请求
    void handleRequest(const std::string& request, std::function<void(const std::string&)> callback);

    // 处理来自客户端的连接
    void handleAccept(const asio::error_code& error);

    // 处理读取操作的结果
    void handleRead(const asio::error_code& error, size_t bytes_transferred);

    // 处理写入操作的结果
    void handleWrite(const asio::error_code& error, size_t bytes_transferred);

    // 关闭连接
    void closeConnection();
};

#endif // RPCSERVER_H
