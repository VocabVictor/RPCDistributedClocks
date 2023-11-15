#ifndef SOCKET_H
#define SOCKET_H

#include <string>
#if defined(_WIN32)
    #include <winsock2.h>
    #include <Ws2tcpip.h>
    typedef SOCKET socket_t;
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    typedef int socket_t;
#endif


// 定义动态库导出宏
#if defined(_WIN32) || defined(__CYGWIN__)
#define RPC_SOCKET_API __declspec(dllexport)
#else
#define RPC_SOCKET_API
#endif

class RPC_SOCKET_API RpcSocket {
public:
    RpcSocket();
    ~RpcSocket();

    void create();
    void bind(int port);
    void listen(int backlog = 10) const;
    RpcSocket accept();
    void connect(const std::string& address, int port);
    int receiveData(char* buf, int len, int flags) const;
    int sendData(const char* buf, int len, int flags) const;
    void close();
    bool isValid() const;

private:
    socket_t sockfd_;
    struct sockaddr_in address_{};
};

#endif // SOCKET_H
