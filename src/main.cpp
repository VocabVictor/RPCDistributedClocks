#include "main.h"
#include <iostream>

CommandLineParser::CommandLineParser(int argc, char* argv[]) {
    _isManager = false;
    _isWorker = false;
    _isHelp = false;
    _isVersion = false;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "--help" || arg == "-h") {
            _isHelp = true;
            break;
        } else if( arg == "--version" || arg == "-v" ){
            _isVersion = true;
            break;
        }
        if( i + 1 < argc ){
            if ( arg == "--mode" || arg == "-m"  ) {
                std::string mode = argv[++i];
                if (mode == "manager") {
                    _isManager = true;
                } else if (mode == "worker") {
                    _isWorker = true;
                }
            }
            else if( arg == "--port" || arg == "-p" ){
                _port = std::stoi(argv[++i]);
            }
            else if( arg == "--address" || arg == "-a" ){
                _address = argv[++i];
            }
            else {
                break;
            }
        }
    }

    if (_isManager && _isWorker) {
        // 参数冲突，不能同时是manager和worker
        _isHelp = true;
    }
}

void CommandLineParser::printHelp() {
    std::cout << "Usage: distributed_clocks --mode [manager|worker] [options]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << " --help | -h : print this help message" << std::endl;
    std::cout << " --version | -v: print version information" << std::endl;
    std::cout << "  --mode | -m: specify the mode of the program, either manager or worker" << std::endl;
}

void CommandLineParser::printVersion() const {
    std::cout << "distributed_clocks version " << _version << std::endl;
}

void CommandLineParser::run() const {
    if(_isVersion){
        printVersion();
        return;
    }

    if (_isHelp) {
        printHelp();
        return;
    }

    if (_isManager) {
        ManagerNode node(12345);
        node.start();
    }
    else if(_isWorker) {
        WorkerNode node("127.0.0.1",1080);
        node.connectToManager("127.0.0.1", 12345);
    }
    else {
        std::cout << "Error: no mode specified." << std::endl;
    }
}

int main(int argc, char* argv[]) {
    // 解析命令行参数，确定是作为管理器还是工作节点运行
    CommandLineParser cmdParser(argc, argv);

    cmdParser.run();

    return 0;
}

