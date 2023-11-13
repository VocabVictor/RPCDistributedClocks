
#ifndef RPCCLIENT_H
#define RPCCLIENT_H

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

class DLL_EXPORT RpcClient {
public:
    // 构造函数
    RpcClient(asio::io_context& io_context, const std::string& serverAddress, int serverPort);

    // 析构函数
    virtual ~RpcClient();

    // 连接到 RPC 服务器
    void connect();

    // 异步连接到服务器
    void asyncConnect();

    // 断开与 RPC 服务器的连接
    void disconnect();

    // 同步调用远程过程
    std::string call(const std::string& procedureName, const std::string& args);

    // 异步调用远程过程
    void asyncCall(const std::string& procedureName, const std::string& args, std::function<void(const std::string&)> callback);

    // 处理接收到的数据
    void handleRead(const asio::error_code& error, size_t bytes_transferred);

    // 处理发送的数据
    void handleWrite(const asio::error_code& error, size_t bytes_transferred);

private:
    asio::io_context& io_context_; // 引用外部的 io_context
    asio::ip::tcp::socket socket_; // 用于通信的 socket
    std::string serverAddress_;    // 服务器地址
    int serverPort_;               // 服务器端口
    asio::streambuf request_;      // 存储请求数据的缓冲区
    asio::streambuf response_;     // 存储响应数据的缓冲区
    bool isConnected; // 连接状态标志

    // 私有方法
    void doRead();
    void doWrite(const std::string& message);
};

#endif // RPCCLIENT_H
