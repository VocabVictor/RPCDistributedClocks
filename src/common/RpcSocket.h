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
#define SOCKET __declspec(dllexport)
#else
#define SOCKET
#endif

class SOCKET Socket {
public:
    Socket();
    ~Socket();

    void create();
    void bind(int port);
    void listen(int backlog = 10) const;
    Socket accept();
    void connect(const std::string& address, int port);
    ssize_t receiveData(char* buf, size_t len, int flags);
    ssize_t sendData(const char* buf, size_t len, int flags);
    void close();

private:
    socket_t sockfd_;
    struct sockaddr_in address_;
};

#endif // SOCKET_H
