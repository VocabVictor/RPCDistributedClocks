#ifndef TIMECOLLECTOR_H
#define TIMECOLLECTOR_H

#include <string>
#include <vector>

// 定义动态库导出宏
#if defined(_WIN32) || defined(__CYGWIN__)
#define TIME_COLLECTOR __declspec(dllexport)
#else
#define TIME_COLLECTOR
#endif

class TIME_COLLECTOR TimeCollector {
public:
    TimeCollector(); // 构造函数

    // 添加时间记录
    void addTimeRecord(const std::string& timeRecord);

    // 获取所有时间记录
    const std::vector<std::string>& getAllTimeRecords() const;

    // 计算平均时间
    double calculateAverageTime() const;

private:
    std::vector<std::string> timeRecords; // 存储时间记录的容器
};

#endif // TIMECOLLECTOR_H
