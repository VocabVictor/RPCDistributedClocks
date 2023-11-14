#include "CommandLineParser.h"
#include <string>

CommandLineParser::CommandLineParser(int argc, char* argv[]) {
    _isManagerNode = false;
    _isWorkerNode = false;
    _isRpcServer = false;
    _isRpcClient = false;
    _isHelp = false;

    _managerNodeAddress = "";
    _workerNodeAddress = "";
    _rpcServerAddress = "";
    _rpcClientAddress = "";

    if (argc < 2) {
        _isHelp = true;
        return;
    }

    std::string mode(argv[1]);

    if (mode == "manager") {
        _isManagerNode = true;
        if (argc < 3) {
            _isHelp = true;
            return;
        }
        _managerNodeAddress = argv[2];
    } else if (mode == "worker") {
        _isWorkerNode = true;
        if (argc < 3) {
            _isHelp = true;
            return;
        }
        _workerNodeAddress = argv[2];
    } else if (mode == "rpcserver") {
        _isRpcServer = true;
        if (argc < 3) {
            _isHelp = true;
            return;
        }
        _rpcServerAddress = argv[2];
    } else if (mode == "rpcclient") {
        _isRpcClient = true;
        if (argc < 3) {
            _isHelp = true;
            return;
        }
        _rpcClientAddress = argv[2];
    } else {
        _isHelp = true;
        return;
    }
}

CommandLineParser::~CommandLineParser() {

}

bool CommandLineParser::isManagerNode() const {
    return _isManagerNode;
}

bool CommandLineParser::isWorkerNode() const {
    return _isWorkerNode;
}

bool CommandLineParser::isRpcServer() const {
    return _isRpcServer;
}

bool CommandLineParser::isRpcClient() const {
    return _isRpcClient;
}

bool CommandLineParser::isHelp() const {
    return _isHelp;
}

std::string CommandLineParser::getManagerNodeAddress() const {
    return _managerNodeAddress;
}

std::string CommandLineParser::getWorkerNodeAddress() const {
    return _workerNodeAddress;
}

std::string CommandLineParser::getRpcServerAddress() const {
    return _rpcServerAddress;
}

std::string CommandLineParser::getRpcClientAddress() const {
    return _rpcClientAddress;
}



