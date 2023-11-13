#ifndef RPCCLIENT_H
#define RPCCLIENT_H

#include <string>
#include <iostream>
// 可能还需要其他头文件，例如网络通信或线程相关的库

class RpcClient {
public:
    RpcClient(const std::string& serverAddress, int port);
    ~RpcClient();

    void connectToServer();
    std::string sendRequest(const std::string& request);
    void closeConnection();

private:
    std::string serverAddress;
    int serverPort;
    // 根据所使用的网络库，您可能需要定义更多的成员变量来管理连接

    // 私有方法可以在这里定义
};

#endif // RPCCLIENT_H
