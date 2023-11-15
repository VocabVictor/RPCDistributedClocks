#ifndef RPCCLIENT_H
#define RPCCLIENT_H

#include "../common//RpcChannel.h"
#include "../common/RpcProtocol.h"

// 定义动态库导出宏
#if defined(_WIN32) || defined(__CYGWIN__)
#define RPC_CLIENT __declspec(dllexport)
#else
#define RPC_CLIENT
#endif

class RPC_CLIENT RpcClient {
public:
    RpcClient(int Port);

    void connect(const std::string& address,int port);
    void disconnect();

    // 发送请求并接收响应
    RpcProtocol::RpcResponse sendRequest(const RpcProtocol::RpcRequest& request);

private:
    RpcChannel channel_;
};

#endif // RPCCLIENT_H
