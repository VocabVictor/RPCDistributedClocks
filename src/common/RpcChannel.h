#ifndef RPCCHANNEL_H
#define RPCCHANNEL_H

#if defined(_WIN32) || defined(__CYGWIN__)
#define RPC_CHANNEL __declspec(dllexport)
#else
#define RPC_CHANNEL
#endif

#include <functional>
#include "RpcSocket.h"
#include "RpcProtocol.h"

class RPC_CHANNEL RpcChannel {
public:

    explicit RpcChannel(int port);
    explicit RpcChannel(RpcSocket& socket);
    ~RpcChannel();

    void connect(const std::string& address, int port);
    void disconnect();

    [[noreturn]] void listenAndAccept(std::function<void(RpcChannel)> clientHandler);

    RpcProtocol::RpcResponse sendRequest(const RpcProtocol::RpcRequest& request);
    RpcProtocol::RpcRequest receiveRequest();
    void sendResponse(const RpcProtocol::RpcResponse& response);

private:
    RpcSocket socket_;
    std::string address_;
    int port_{};
};

#endif // RPCCHANNEL_H
