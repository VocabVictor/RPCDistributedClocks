#ifndef MANAGERMAIN_H
#define MANAGERMAIN_H

// 定义动态库导出宏
#if defined(_WIN32) || defined(__CYGWIN__)
#define MANAGER_MAIN __declspec(dllexport)
#else
#define MANAGER_MAIN
#endif

class MANAGER_MAIN ManagerMain {
public:
    ManagerMain(); // 构造函数

    // 启动管理器
    void start();

    // 停止管理器
    void stop();

private:
    bool isRunning; // 管理器运行状态
};

#endif // MANAGERMAIN_H
