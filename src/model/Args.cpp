#include "Args.hpp"

void readArgs(std::map <std::string, std::vector<std::string>> &args) {
/*
    if (args.contains("-h") || args.contains("--help")) {
        std::cout << "./ggraph [-a | --algo, -n | --nodes, -v | --version, --debug, -p | --probability, -t | --templates]" << std::endl;
        exit(EXIT_SUCCESS);
    }

    if (args.contains("-v") || args.contains("--version")) {
        std::cout << "Graph v" << PROJECT_VERSION << std::endl;
        exit(EXIT_SUCCESS);
    }

    if (args.contains("--debug")) {
        Logger::setLogLevel(LogLevel::DEBUG);
    } else {
        Logger::setLogLevel(LogLevel::INFO);
    }
*/
}

void runGraphArgs(std::map<std::string, std::vector<std::string>> &args) {
/*    Graph g;

    if ((args.contains("-f") || args.contains("--file")) && (args.contains("-a") || args.contains("--algo"))) {
        std::vector<std::string> fArgs = args.contains("-f") ? args["-f"] : args["--file"];

        std::vector<std::string> algoArgs = args.contains("-a") ? args["-a"] : args["--algo"];

        std::string filename;

        if (fArgs[0] == "random") {
            if (fArgs.size() != 3) {
                Logger::error("Invalid number of arguments for random graph", __CONTEXT__);
                exit(EXIT_FAILURE);
            } else {
                int n = std::stoi(fArgs[1]);
                double p = std::stod(fArgs[2]);
                g = Graph::createRandomGraph(n, p);

                filename = "random_" + std::to_string(n) + "_" + std::to_string(p);

                std::string inFilename = "../instances/" + (algoArgs[0] == "all" ? "new_instances" : algoArgs[0]) + "/" + filename + ".in";

                iofile::writeInputFile(inFilename, g);
            }
        } else {
            filename = fArgs[0];

            std::string readFilename = "../instances/" + (algoArgs[0] == "all" ? "new_instances" : algoArgs[0]) + "/" + filename + ".in";

            g = iofile::readFile(readFilename);
        }

        // Run algo
        if (algoArgs[0] == "exact") {
            std::string outFilename = "../instances/" + algoArgs[0] + "/" + filename + "_" + algoArgs[0] + ".out";

            iofile::writeResultFile(outFilename, g, algoArgs[0]);
        } else if (algoArgs[0] == "constructive") {
            std::string outFilename = "../instances/" + algoArgs[0] + "/" + filename + ".out";

            iofile::writeResultFile(outFilename, g, algoArgs[0]);
        } else if (algoArgs[0] == "local_search") {
            std::string outFilename = "../instances/" + algoArgs[0] + "/" + filename + ".out";

            iofile::writeResultFile(outFilename, g, algoArgs[0]);
        } else if (algoArgs[0] == "tabu_search") {
            std::string outFilename = "../instances/" + algoArgs[0] + "/" + filename + ".out";

            iofile::writeResultFile(outFilename, g, algoArgs[0]);
        } else if (algoArgs[0] == "all") {
            iofile::writeResultFile("../instances/exact/" + filename + ".out", g, "exact");
            iofile::writeResultFile("../instances/constructive/" + filename + ".out", g, "constructive");
            iofile::writeResultFile("../instances/local_search/" + filename + ".out", g, "local_search");
            iofile::writeResultFile("../instances/tabu_search/" + filename + ".out", g, "tabu_search");
        } else {
            Logger::error("Invalid algorithm name", __CONTEXT__);
            exit(EXIT_FAILURE);
        }
    }*/
}
