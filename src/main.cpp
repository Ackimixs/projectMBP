#include "model/iofile.hpp"
#include "model/Args.hpp"

int main(int argc, char* argv[]) {

    // Convert argv to map
    std::map<std::string, std::vector<std::string>> args;

    for (int i = 0; i < argc; i++) {
        auto arg = std::string(argv[i]);
        if (arg[0] == '-') {
            args[arg] = std::vector<std::string>();
            for (int j = i + 1; j < argc; j++) {
                std::string arg2 = argv[j];
                if (arg2[0] == '-') {
                    break;
                } else {
                    args[arg].push_back(arg2);
                }
            }
        }
    }

    readArgs(args);

    Logger::info(LogColor::fgMagenta + "STARTING PROGRAM" + LogColor::reset, __CONTEXT__);

    runGraphArgs(args);

//    std::string filename = "first_test";
//    std::string filename = "random";
//    std::string filename = "test";

//    Graph g = iofile::readFile(filename);
//    Graph g = Graph::createRandomGraph(1000, .75);

//    iofile::writeResultFile(filename, g, "exact");
//    iofile::writeResultFile(filename, g, "constructive");
//    iofile::writeResultFile(filename, g, "local_search");
//    iofile::writeResultFile(filename, g, "tabu_search");
//    iofile::writeInputFile(filename, g);

    Logger::info(LogColor::fgMagenta + "PROGRAM ENDED" + LogColor::reset, __CONTEXT__);

    return 0;
}
