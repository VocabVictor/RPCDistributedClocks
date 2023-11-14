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
        // 可能的其他操作类型...
    };

    // 时间请求消息的结构
    struct TimeRequest {
        // 可以包含特定的请求细节，如请求者ID等
    };

    // 时间响应消息的结构
    struct TimeResponse {
        std::string time; // 包含时间信息
    };

    // RPC 请求消息的结构
    struct RpcRequest {
        OperationType type; // 操作类型
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

    // 辅助函数，应用导出宏
    std::string RPC_PROTOCOL getCurrentTime(); // 获取当前时间的函数
    std::string RPC_PROTOCOL averageTime(const std::vector<std::string>& times); // 计算平均时间的函数
}
#endif // RPCPROTOCOL_H
