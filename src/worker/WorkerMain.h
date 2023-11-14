#ifndef WORKERMAIN_H
#define WORKERMAIN_H

#include <string>

// 定义动态库导出宏
#if defined(_WIN32) || defined(__CYGWIN__)
#define WORKER_MAIN __declspec(dllexport)
#else
#define WORKER_MAIN
#endif

class WORKER_MAIN WorkerMain {
public:
    WorkerMain(); // 构造函数

    // 启动 Worker
    void start();

    // 停止 Worker
    void stop();

    // 执行任务
    void executeTask(const std::string& task);

private:
    bool isRunning; // Worker 运行状态
};

#endif // WORKERMAIN_H
