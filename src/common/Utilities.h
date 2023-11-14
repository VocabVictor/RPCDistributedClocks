// common/Utilities.h

#ifndef UTILITIES_H
#define UTILITIES_H

#include <vector>
#include <string>

// 定义导出宏
#if defined(_WIN32) || defined(__CYGWIN__)
#define UTILITIES_API __declspec(dllexport)
#else
#define UTILITIES_API
#endif

namespace Utilities {

    // 将字符串分割为子字符串
    std::vector<std::string> UTILITIES_API splitString(const std::string& input, char delimiter);

    // 移除字符串两端的空白字符
    std::string UTILITIES_API trim(const std::string& input);

    // 获取当前系统时间的字符串表示
    std::string UTILITIES_API getCurrentTime();

} // namespace Utilities

#endif // UTILITIES_H
