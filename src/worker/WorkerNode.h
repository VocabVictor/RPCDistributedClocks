#ifndef WORKERNODE_H
#define WORKERNODE_H

// 定义动态库导出宏
#if defined(_WIN32) || defined(__CYGWIN__)
#define WORKER_NODE __declspec(dllexport)
#else
#define WORKER_NODE
#endif

class WORKER_NODE WorkerNode {
public:
    WorkerNode(); // 构造函数

    // 初始化节点
    void initialize();

    // 启动节点
    void start();

    // 停止节点
    void stop();

private:
    bool isInitialized; // 节点初始化状态
    bool isRunning;     // 节点运行状态
};

#endif // WORKERNODE_H
