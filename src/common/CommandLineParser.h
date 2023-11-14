//
// Created by teenager on 2023/11/14.
//

#ifndef RPCDISTRIBUTEDCLOCKS_COMMANDLINEPARSER_H
#define RPCDISTRIBUTEDCLOCKS_COMMANDLINEPARSER_H

#include <string>

// 定义动态库导出宏
#if defined(_WIN32) || defined(__CYGWIN__)
#define COMMAND_LINE_PARSER __declspec(dllexport)
#else
#define COMMAND_LINE_PARSER
#endif

class COMMAND_LINE_PARSER CommandLineParser {
    public:
        CommandLineParser(int argc, char* argv[]);
        ~CommandLineParser();

        bool isManagerNode() const;
        bool isWorkerNode() const;
        bool isRpcServer() const;
        bool isRpcClient() const;
        bool isHelp() const;

        std::string getManagerNodeAddress() const;
        std::string getWorkerNodeAddress() const;
        std::string getRpcServerAddress() const;
        std::string getRpcClientAddress() const;
private:
    bool _isManagerNode;
    bool _isWorkerNode;
    bool _isRpcServer;
    bool _isRpcClient;
    bool _isHelp;

    std::string _managerNodeAddress;
    std::string _workerNodeAddress;
    std::string _rpcServerAddress;
    std::string _rpcClientAddress;

};


#endif //RPCDISTRIBUTEDCLOCKS_COMMANDLINEPARSER_H
