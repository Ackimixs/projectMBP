#include "model/iofile.hpp"
#include "model/Args.hpp"

int main(int argc, char* argv[]) {
    Logger::setLogLevel(LogLevel::DEBUG);

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

    if (std::string(argv[1]) == "generate") {
        runGraphRandomArgs(args);
    } else if (std::string(argv[1]) == "algo") {
        std::string algoName = argv[2];

        runGraphAlgoArgs(args, algoName);
    }

    // LOCAL TEST
    // TODO REMOVE THIS AT THE END

//    std::string filename = "first_test";
//    std::string filename = "random";
//    std::string filename = "test";

//    Graph g = iofile::readFile(filename + ".in");
//    Graph g = Graph::createRandomGraph(1000, .50);

//    iofile::writeResultFile(filename + "_exact.out", g, "exact");
//    iofile::writeResultFile(filename + "_constructive.out", g, "constructive");
//    iofile::writeResultFile(filename + "_constructive_V5.out", g, "constructive_V5");
//    iofile::writeResultFile(filename + "_local_search.out", g, "local_search");
//    iofile::writeResultFile(filename + "_local_search_V2.out", g, "local_search_V2");
//    iofile::writeResultFile(filename + "_local_search_V3.out", g, "local_search_V3");
//    iofile::writeResultFile(filename + "_tabu_search.out", g, "tabu_search");
//    iofile::writeInputFile(filename + ".in", g);


    Logger::info(LogColor::fgMagenta + "PROGRAM ENDED" + LogColor::reset, __CONTEXT__);

    return 0;
}
