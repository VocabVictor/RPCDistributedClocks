#ifndef MAIN_H
#define MAIN_H

// 包含必要的头文件
#include "rpc/RpcClient.h"        // RPC客户端
#include "rpc/RpcServer.h"        // RPC服务器
#include "common/Utilities.h"     // 通用工具
#include "manager/ManagerNode.h" // 管理节点
#include "worker/WorkerNode.h"   // 工作节点

// 全局常量或变量（如有）

// 主要应用逻辑的函数原型
void startManagerNode();       // 启动管理节点
void startWorkerNode();        // 启动工作节点
void configureRpcServer();     // 配置RPC服务器

// 主函数声明
int main(int argc, char* argv[]);

#endif // MAIN_H
