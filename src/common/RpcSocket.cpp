#include "RpcSocket.h"
#include <iostream>

RpcSocket::RpcSocket() : sockfd_(-1) {
#if defined(_WIN32)
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Winsock initialization failed." << std::endl;
    }
#endif
}

RpcSocket::~RpcSocket() {
#if defined(_WIN32)
    WSACleanup();
#endif
}

void RpcSocket::create() {
    sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd_ == -1) {
        std::cerr << "Failed to create socket: " << strerror(errno) << std::endl;
        throw std::runtime_error("Failed to create socket: " + std::string(strerror(errno)));
    }
}

void RpcSocket::bind(int port) {
    address_.sin_family = AF_INET;
    address_.sin_addr.s_addr = INADDR_ANY;
    address_.sin_port = htons(port);

    if (::bind(sockfd_, (struct sockaddr *)&address_, sizeof(address_)) < 0) {
        std::cerr << "RpcSocket bind failed." << std::endl;
    }
}

void RpcSocket::listen(int backlog) const {
    if (::listen(sockfd_, backlog) < 0) {
        std::cerr << "RpcSocket listen failed." << std::endl;
    }
}

RpcSocket RpcSocket::accept() {
    int addrlen = sizeof(address_);
    socket_t client_sockfd = ::accept(sockfd_, (struct sockaddr *)&address_, &addrlen);
    if (client_sockfd == -1) {
        return {}; // 返回一个无效的 RpcSocket 对象
    }

    RpcSocket clientRpcSocket;
    clientRpcSocket.sockfd_ = client_sockfd;
    return clientRpcSocket;
}

void RpcSocket::close() {
#if defined(_WIN32)
    if (sockfd_ != INVALID_SOCKET) {
        closesocket(sockfd_);
        sockfd_ = INVALID_SOCKET;
        std::cout << "Socket closed." << std::endl;
    }
#else
    if (sockfd_ != -1) {
        ::close(sockfd_);
        sockfd_ = -1;
    }
#endif
}

int RpcSocket::receiveData(char* buf, int len, int flags) const {
    return ::recv(sockfd_, buf, len, flags);
}

int RpcSocket::sendData(const char* buf, int len, int flags) const {
    return ::send(sockfd_, buf, len, flags);
}

void RpcSocket::connect(const std::string& address, int port) {
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    #if defined(_WIN32)
        if (InetPton(AF_INET, address.c_str(), &serv_addr.sin_addr) != 1) {
            std::cerr << "Invalid address/ Address not supported" << std::endl;
        }
    #else
        if (inet_pton(AF_INET, address.c_str(), &serv_addr.sin_addr) <= 0) {
            std::cerr << "Invalid address/ Address not supported" << std::endl;
        }
    #endif

    if (::connect(sockfd_, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection failed" << std::endl;
    }
}

bool RpcSocket::isValid() const  {
    return sockfd_ != -1;
}