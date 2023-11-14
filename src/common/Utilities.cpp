// common/Utilities.cpp

#include "Utilities.h"

#include <sstream>

namespace Utilities {

    // 将字符串分割为子字符串
    std::vector<std::string> UTILITIES_API splitString(const std::string& input, char delimiter) {
        std::vector<std::string> tokens;
        std::istringstream tokenStream(input);
        std::string token;
        while (std::getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    // 移除字符串两端的空白字符
    std::string UTILITIES_API trim(const std::string& input) {
        std::string trimmed = input;
        size_t start = trimmed.find_first_not_of(" \t\n\r");
        size_t end = trimmed.find_last_not_of(" \t\n\r");
        if (start != std::string::npos && end != std::string::npos) {
            return trimmed.substr(start, end - start + 1);
        }
        return "";
    }

    // 获取当前系统时间的字符串表示
    std::string UTILITIES_API getCurrentTime() {
        // 实现获取当前系统时间的逻辑
        // 这里仅返回一个示例字符串，您需要根据实际情况实现
        return "2023-03-15 12:00:00";
    }

} // namespace Utilities
