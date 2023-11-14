#ifndef CLOCKSERVICE_H
#define CLOCKSERVICE_H

#include <string>
#include <chrono>

// 定义动态库导出宏
#if defined(_WIN32) || defined(__CYGWIN__)
#define CLOCK_SERVICE __declspec(dllexport)
#else
#define CLOCK_SERVICE
#endif

class CLOCK_SERVICE ClockService {
public:
    ClockService(); // 构造函数

    // 获取当前节点的时间戳
    std::chrono::time_point<std::chrono::system_clock> getCurrentTimestamp() const;

    // 同步本地时钟
    void synchronizeClock(const std::chrono::time_point<std::chrono::system_clock>& externalTimestamp);

    // 获取节点ID
    std::string getNodeID() const;

private:
    std::string nodeID; // 节点唯一标识
};

#endif // CLOCKSERVICE_H
