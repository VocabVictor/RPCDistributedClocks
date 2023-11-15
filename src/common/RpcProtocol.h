#ifndef RPCPROTOCOL_H
#define RPCPROTOCOL_H

#include <string>
#include <vector>

// 定义动态库导出宏
#if defined(_WIN32) || defined(__CYGWIN__)
#define RPC_PROTOCOL __declspec(dllexport)
#else
#define RPC_PROTOCOL
#endif


namespace RpcProtocol {

    // RPC 操作类型
    enum class OperationType {
        RequestTime, // 请求时间
        SendTime,    // 发送时间
        Service,     // 服务
        Invalid     // 无效操作
    };

    // RPC 请求消息的结构
    struct RpcRequest {
        OperationType type;  // 操作类型
        std::string serviceName;  // 服务名称
        std::string data;   // 用于序列化的数据，可能是 TimeRequest 的序列化形式
    };

    // RPC 响应消息的结构
    struct RpcResponse {
        bool success;       // 操作是否成功
        std::string data;   // 响应数据，可能是 TimeResponse 的序列化形式
    };

    // 序列化和反序列化函数，应用导出宏
    std::string RPC_PROTOCOL serialize(const RpcRequest& request);
    RpcRequest RPC_PROTOCOL deserializeRequest(const std::string& data);

    std::string RPC_PROTOCOL serialize(const RpcResponse& response);
    RpcResponse RPC_PROTOCOL deserializeResponse(const std::string& data);

}
#endif // RPCPROTOCOL_H
