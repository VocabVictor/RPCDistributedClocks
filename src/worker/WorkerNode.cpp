#include "WorkerNode.h"

WorkerNode::WorkerNode() {
    // 在构造函数中进行初始化，如果有必要的话
    isInitialized = false;
    isRunning = false;
}

void WorkerNode::initialize() {
    // 在此处添加节点初始化的逻辑
    isInitialized = true;
}

void WorkerNode::start() {
    // 在此处添加节点启动的逻辑
    if (!isInitialized) {
        initialize(); // 如果节点未初始化，则先进行初始化
    }
    isRunning = true;
    // 启动其他操作...
}

void WorkerNode::stop() {
    // 在此处添加节点停止的逻辑
    isRunning = false;
    // 停止其他操作...
}
