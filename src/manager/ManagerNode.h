#ifndef MANAGERNODE_H
#define MANAGERNODE_H

// 定义动态库导出宏
#if defined(_WIN32) || defined(__CYGWIN__)
#define MANAGER_NODE __declspec(dllexport)
#else
#define MANAGER_NODE
#endif

class MANAGER_NODE ManagerNode {
public:
    ManagerNode(); // 构造函数

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

#endif // MANAGERNODE_H
