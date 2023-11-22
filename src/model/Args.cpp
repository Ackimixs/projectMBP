#include "Args.hpp"

void readArgs(std::map <std::string, std::vector<std::string>> &args) {
    if (args.find("-h") != args.end() || args.find("--help") != args.end()) {
        std::cout << "./ggraph [-a | --algo, -n | --nodes, -v | --version, --debug, -p | --probability, -t | --templates]" << std::endl;
        exit(EXIT_SUCCESS);
    }

    if (args.find("-v") != args.end() || args.find("--version") != args.end()) {
        std::cout << "Graph v" << PROJECT_VERSION << std::endl;
        exit(EXIT_SUCCESS);
    }

    if (args.find("--debug") != args.end()) {
        Logger::setLogLevel(LogLevel::DEBUG);
    } else {
        Logger::setLogLevel(LogLevel::INFO);
    }
}

void runGraphAlgoArgs(std::map<std::string, std::vector<std::string>> &args) {
    Graph g;

    if ((args.find("-f") != args.end()  || args.find("--file") != args.end() ) && (args.find("-a") != args.end()  || args.find("--algo") != args.end() )) {
        std::vector<std::string> fArgs = args.find("-f") != args.end()  ? args["-f"] : args["--file"];

        std::vector<std::string> algoArgs = args.find("-a") != args.end()  ? args["-a"] : args["--algo"];

        std::string filename;

        filename = fArgs[0];

        std::string readFilename = "../instances/" + (algoArgs[0] == "all" ? "new_instances" : algoArgs[0]) + "/" + filename + ".in";

        g = iofile::readFile(readFilename);

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
    }
}

void runGraphRandomArgs(std::map<std::string, std::vector<std::string>> &args) {

    int n = 1000;
    double p = .5;

    Graph g;

    if (args.find("-n") != args.end() || args.find("--nodes") != args.end()) {
        std::vector<std::string> nArgs = args.find("-n") != args.end() ? args["-n"] : args["--nodes"];

        n = std::stoi(nArgs[0]);
    }

    if (args.find("-p") != args.end() || args.find("--probability") != args.end()) {
        std::vector<std::string> pArgs = args.find("-p") != args.end() ? args["-p"] : args["--probability"];

        p = std::stod(pArgs[0]);
    }

    std::string filename;

    if (args.find("-f") != args.end() || args.find("--file") != args.end()) {
        std::vector<std::string> fArgs = args.find("-f") != args.end() ? args["-f"] : args["--file"];

        filename = fArgs[0];
    } else {
        filename = "random_" + std::to_string(n) + "_" + std::to_string(p) + ".in";
    }

    Logger::debug("Generating graph with " + std::to_string(n) + " nodes and " + std::to_string(p) + " probability and save it to : " + filename, __CONTEXT__);

    g = Graph::createRandomGraph(n, p);
    iofile::writeInputFile(filename, g);
}