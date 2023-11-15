#ifndef MAIN_H
#define MAIN_H

// 包含必要的头文件
#include "manager/ManagerNode.h"  // 管理器主要类
#include "worker/WorkerNode.h"    // 工作者主要类

class CommandLineParser {
public:
    CommandLineParser(int argc, char* argv[]);

    static void printHelp() ;
    void printVersion() const;
    void run() const;

private:
    bool _isManager;
    bool _isWorker;
    bool _isHelp;
    bool _isVersion;
    const std::string _version = "0.1.0";
    std::string _address;
    int _port;
};

// 主函数声明
int main(int argc, char* argv[]);

#endif // MAIN_H
