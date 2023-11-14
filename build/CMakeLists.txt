cmake_minimum_required(VERSION 3.10)

project(RPCDistributedClocks VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    add_definitions(-D_WIN32_WINNT=0x0601)
endif()

if(MSVC)
    add_compile_options(/wd4251)  # 忽略警告 C4251
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../bin/dll)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ../bin)

add_library(rpc SHARED
        ../src/rpc/RpcClient.cpp
        ../src/rpc/RpcClient.h
         ../src/rpc/RpcServer.cpp
         ../src/rpc/RpcServer.h
)

add_library(common SHARED
        ../src/common/RpcProtocol.cpp
        ../src/common/RpcProtocol.h
        ../src/common/Utilities.cpp
        ../src/common/Utilities.h
        ../src/common/CommandLineParser.cpp
        ../src/common/CommandLineParser.h
)

add_library(
        manager SHARED
        ../src/manager/ManagerMain.cpp
        ../src/manager/ManagerMain.h
        ../src/manager/ManagerNode.cpp
        ../src/manager/ManagerNode.h
        ../src/manager/TimeCollector.cpp
        ../src/manager/TimeCollector.h
)

add_library(
        worker SHARED
        ../src/worker/ClockService.cpp
        ../src/worker/ClockService.h
        ../src/worker/WorkerMain.cpp
        ../src/worker/WorkerMain.h
        ../src/worker/WorkerNode.cpp
        ../src/worker/WorkerNode.h
)

add_executable(RPCDistributedClocks
        ../src/main.cpp
        ../src/main.h)

target_link_libraries(RPCDistributedClocks rpc)
target_link_libraries(RPCDistributedClocks common)
target_link_libraries(RPCDistributedClocks worker)
target_link_libraries(RPCDistributedClocks manager)

target_compile_options(RPCDistributedClocks PUBLIC -DASIO_STANDALONE)
target_include_directories(RPCDistributedClocks PUBLIC ${ASIO_INCLUDE})

# 针对 Windows 平台的特定链接
if(WIN32)
    target_link_libraries(RPCDistributedClocks wsock32 ws2_32)
endif()


# 其他配置（如测试）可以在这里继续
#enable_testing()
#add_subdirectory(../tests)
