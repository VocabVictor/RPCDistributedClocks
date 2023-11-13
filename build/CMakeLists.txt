# CMake最小版本要求
# 指定构建本项目所需的最小CMake版本
cmake_minimum_required(VERSION 3.10)

# 项目信息
# 设定项目名称和版本号
project(RPCDistributedClocks VERSION 1.0)

# C++标准设置
# 设置C++标准为C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 构建类型
# 如果未指定构建类型，默认设为Release模式
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# 设置输出目录
# 所有的可执行文件和库都会被放置在这个目录下
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ../bin)

# 包含目录
# 添加项目中的include目录路径
#include_directories(../src/common)
#include_directories(../src/manager)
#include_directories(../src/worker)
#include_directories(../src/rpc)

# 子目录
# 添加各个子模块的目录，子目录中应该还有CMakeLists.txt文件
#add_subdirectory(../src/common)
#add_subdirectory(../src/manager)
#add_subdirectory(../src/worker)
#add_subdirectory(../src/rpc)

# 可执行文件
# 指定生成可执行文件，以及相关的源文件
add_executable(RPCDistributedClocks
        ../src/main.cpp
        ../src/main.h)

# 链接库文件
# 将可执行文件与所需的库文件进行链接
#target_link_libraries(RPCDistributedClocks common manager worker rpc)

# 编译选项
# 为目标添加编译选项，如有需要可以取消注释
#target_compile_options(RPCDistributedClocks PRIVATE -Wall -Wextra)

# 测试配置
# 开启测试并添加测试子目录，如有需要可以取消注释
#enable_testing()
#add_subdirectory(../tests)
