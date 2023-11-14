#include "TimeCollector.h"

TimeCollector::TimeCollector() {
    // 在构造函数中初始化对象
}

void TimeCollector::addTimeRecord(const std::string& timeRecord) {
    // 将时间记录添加到容器中
    timeRecords.push_back(timeRecord);
}

const std::vector<std::string>& TimeCollector::getAllTimeRecords() const {
    // 返回所有时间记录
    return timeRecords;
}

double TimeCollector::calculateAverageTime() const {
    // 计算平均时间的逻辑
    double averageTime = 0.0;

    // 计算所有时间记录的总和
    for (const std::string& timeRecord : timeRecords) {
        // 在实际情况中，您需要将时间记录转换为数字进行计算
        // 这里仅是一个示例，需要根据实际数据结构进行计算
        // 假设时间记录是浮点数的字符串表示
        double timeValue = std::stod(timeRecord);
        averageTime += timeValue;
    }

    // 计算平均值
    if (!timeRecords.empty()) {
        averageTime /= timeRecords.size();
    }

    return averageTime;
}
