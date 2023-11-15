#include <sstream>
#include <iostream>
#include "RpcProtocol.h"

namespace RpcProtocol {

    std::string RPC_PROTOCOL serialize(const RpcRequest& request) {
        std::stringstream ss;
        ss << "RequestType: " << static_cast<int>(request.type) << "; ";
        ss << "ServiceName: " << request.serviceName << "; ";
        ss << "Data: " << request.data;
        return ss.str();
    }

    RpcRequest RPC_PROTOCOL deserializeRequest(const std::string& data) {

        RpcRequest request;
        std::istringstream iss(data);
        std::string segment;

        while (std::getline(iss, segment, ';')) {
            std::istringstream segmentStream(segment);
            std::string key;
            std::getline(segmentStream, key, ':');
            std::string value;
            std::getline(segmentStream, value);
            value.erase(0, value.find_first_not_of(' ')); // Trim leading space

            if (key == "RequestType") {
                request.type = static_cast<OperationType>(std::stoi(value));
            } else if (key == "ServiceName") {
                request.serviceName = value;
            } else if (key == "Data") {
                request.data = value;
            }
        }

        return request;
    }

    // 将 RpcResponse 序列化为字符串
    std::string RPC_PROTOCOL serialize(const RpcResponse& response) {
        // 创建一个字符串流
        std::stringstream ss;

        // 序列化成功标志
        ss << "Success: " << (response.success ? "true" : "false") << "; ";

        // 序列化响应数据
        ss << "Data: " << response.data;

        // 返回序列化后的字符串
        return ss.str();
    }


    RpcResponse RPC_PROTOCOL deserializeResponse(const std::string& data) {
        RpcResponse response;
        std::istringstream iss(data);

        std::string segment;
        while (std::getline(iss, segment, ';')) {
            std::istringstream segmentStream(segment);
            std::string key;
            if (std::getline(segmentStream, key, ':')) {
                std::string value;
                std::getline(segmentStream, value); // 去掉前导空格
                value.erase(0, value.find_first_not_of(' ')); // Trim leading space

                if (key == "Success") {
                    response.success = (value == "true");
                } else if (key == "Data") {
                    response.data = value;
                }
            }
        }

        return response;
    }


}
