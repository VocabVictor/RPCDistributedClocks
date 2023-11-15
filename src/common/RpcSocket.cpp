#include "Socket.h"
#include <iostream>

Socket::Socket() : sockfd_(-1) {
#if defined(_WIN32)
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Winsock initialization failed." << std::endl;
    }
#endif
}

Socket::~Socket() {
#if defined(_WIN32)
    WSACleanup();
#endif
}

void Socket::create() {
    sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd_ == -1) {
        std::cerr << "Failed to create socket." << std::endl;
    }
}

void Socket::bind(int port) {
    address_.sin_family = AF_INET;
    address_.sin_addr.s_addr = INADDR_ANY;
    address_.sin_port = htons(port);

    if (::bind(sockfd_, (struct sockaddr *)&address_, sizeof(address_)) < 0) {
        std::cerr << "Socket bind failed." << std::endl;
    }
}

void Socket::listen(int backlog) const {
    if (::listen(sockfd_, backlog) < 0) {
        std::cerr << "Socket listen failed." << std::endl;
    }
}

Socket Socket::accept() {
    int addrlen = sizeof(address_);
    socket_t client_sockfd = ::accept(sockfd_, (struct sockaddr *)&address_, &addrlen);
    if (client_sockfd == -1) {
        std::cerr << "Accept failed." << std::endl;
        return Socket(); // 返回一个无效的 Socket 对象
    }

    Socket clientSocket;
    clientSocket.sockfd_ = client_sockfd;
    return clientSocket;
}

void Socket::close() {
#if defined(_WIN32)
    if (sockfd_ != INVALID_SOCKET) {
        closesocket(sockfd_);
        sockfd_ = INVALID_SOCKET;
    }
#else
    if (sockfd_ != -1) {
        ::close(sockfd_);
        sockfd_ = -1;
    }
#endif
}

ssize_t Socket::receiveData(char* buf, size_t len, int flags) {
    return ::recv(sockfd_, buf, len, flags);
}

ssize_t Socket::sendData(const char* buf, size_t len, int flags) {
    return ::send(sockfd_, buf, len, flags);
}

void Socket::connect(const std::string& address, int port) {
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    #if defined(_WIN32)
        if (InetPton(AF_INET, address.c_str(), &serv_addr.sin_addr) != 1) {
            std::cerr << "Invalid address/ Address not supported" << std::endl;
            exit(1);
        }
    #else
        if (inet_pton(AF_INET, address.c_str(), &serv_addr.sin_addr) <= 0) {
            std::cerr << "Invalid address/ Address not supported" << std::endl;
            exit(1);
        }
    #endif

    if (::connect(sockfd_, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection failed" << std::endl;
        exit(1);
    }
}