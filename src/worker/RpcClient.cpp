#include "RpcClient.h"

RpcClient::RpcClient(int Port):channel_(Port) {}

void RpcClient::connect(const std::string& address,int port){
    channel_.connect(address,port);
}

void RpcClient::disconnect() {
    channel_.disconnect();
}

RpcProtocol::RpcResponse RpcClient::sendRequest(const RpcProtocol::RpcRequest& request) {
    // 发送 RPC 请求并接收响应
    return channel_.sendRequest(request);
}
