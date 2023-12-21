#include "Args.hpp"

void readArgs(std::map <std::string, std::vector<std::string>> &args, const int argc, char** argv) {

    if ((args.find("-h") != args.end() || args.find("--help") != args.end()) && argc == 2) {
        std::cout << "Usage : ./projectMBP [generate | algo] [options]" << std::endl;
        std::cout << "Graph v" << PROJECT_VERSION << std::endl;
        std::cout << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "  -h, --help" << std::endl;
        std::cout << "  -v, --version" << std::endl;
        std::cout << "  --debug" << std::endl;
        exit(EXIT_SUCCESS);
    }

    if ((args.find("-h") != args.end() || args.find("--help") != args.end()) && argc > 2 && std::string(argv[1]) == "algo") {
        std::cout << "Usage : ./projectMBP algo <algoName> [options]" << std::endl;
        std::cout << "Graph v" << PROJECT_VERSION << std::endl;
        std::cout << std::endl;
        std::cout << "Algorithms:" << std::endl;
        std::cout << "  exact (For graph size < MAX_EXACT_GRAPH_SIZE constant)" << std::endl;
        std::cout << "  constructive" << std::endl;
        std::cout << "  local_search" << std::endl;
        std::cout << "  tabu_search" << std::endl;
        std::cout << "  all (this run every algorithm with graph template that are inside the ./instances/new_instances)" << std::endl;
        std::cout << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "  -h, --help" << std::endl;
        std::cout << "  -v, --version" << std::endl;
        std::cout << "  --debug" << std::endl;
        std::cout << "  -i, --input [filename]" << std::endl;
        std::cout << "  -o, --output [filename]" << std::endl;
        exit(EXIT_SUCCESS);
    }

    if ((args.find("-h") != args.end() || args.find("--help") != args.end()) && argc > 2 && std::string(argv[1]) == "generate") {
        std::cout << "Usage : ./projectMBP generate [options]" << std::endl;
        std::cout << "Graph v" << PROJECT_VERSION << std::endl;
        std::cout << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "  -h, --help" << std::endl;
        std::cout << "  -v, --version" << std::endl;
        std::cout << "  --debug" << std::endl;
        std::cout << "  -n, --nodes [number, int]" << std::endl;
        std::cout << "  -p, --probability [number, double]" << std::endl;
        std::cout << "  -o, --output [filename]" << std::endl;
        exit(EXIT_SUCCESS);
    }

    if ((args.find("-h") != args.end() || args.find("--help") != args.end()) && argc > 2 && std::string(argv[1]) == "test")
    {
        std::cout << "Usage : ./projectMBP test <algoName> [options]" << std::endl;
        std::cout << "Graph v" << PROJECT_VERSION << std::endl;
        std::cout << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "  -h, --help" << std::endl;
        std::cout << "  -v, --version" << std::endl;
        std::cout << "  --debug" << std::endl;
        std::cout << "  -n, --nodes [list of number, int]" << std::endl;
        std::cout << "  -p, --probability [list of number, double]" << std::endl;
    }

    if (args.find("-v") != args.end() || args.find("--version") != args.end()) {
        std::cout << "Graph v" << PROJECT_VERSION << std::endl;
        exit(EXIT_SUCCESS);
    }

    if (args.find("--debug") != args.end()) {
        Logger::setLogLevel(LogLevel::DEBUG);
    } else if (args.find("--no-log") != args.end()) {
        Logger::setLogLevel(LogLevel::WARNING);
    } else {
        Logger::setLogLevel(LogLevel::INFO);
    }
}

void runGraphAlgoArgs(std::map<std::string, std::vector<std::string>> &args, const std::string& algoName) {
    Graph g;

    if ((args.find("-i") != args.end() || args.find("--input") != args.end()) && (args.find("-o") != args.end() || args.find("--output") != args.end())) {
        std::vector<std::string> iArgs = args.find("-i") != args.end() ? args["-i"] : args["--input"];

        std::vector<std::string> oArgs = args.find("-o") != args.end() ? args["-o"] : args["--output"];

        std::string readFilename = iArgs[0];

        std::string outFilename = oArgs[0];

        g = iofile::readFile(readFilename);

        iofile::writeResultFile(outFilename, g, algoName);
    } else {
        if (algoName == "all") {
            for (const auto &entry : std::filesystem::directory_iterator("../instances/new_instances")) {
                std::string filename = entry.path().string();

                Logger::debug("Reading file : " + filename, __CONTEXT__);

                g = iofile::readFile(filename);

                std::string outFilename = "../results/exact/" + entry.path().filename().string();

                if (g.size() < MAX_EXACT_GRAPH_SIZE) {
                    iofile::writeResultFile(outFilename, g, "exact");
                }

                std::string algoList[] = {"constructive", "local_search", "tabu_search"};

                for (const auto &algo : algoList) {
                    outFilename = "../results/" + algo + "/" + entry.path().filename().string();

                    outFilename = outFilename.substr(0, outFilename.find_last_of('.')) + ".out";

                    iofile::writeResultFile(outFilename, g, algo);
                }
            }
        } else {
            for (const auto &entry : std::filesystem::directory_iterator("../instances/" + algoName)) {
                std::string filename = entry.path().string();

                std::string outFilename = "../results/" + algoName + "/" + entry.path().filename().string();

                outFilename = outFilename.substr(0, outFilename.find_last_of('.')) + ".out";

                Logger::debug("Reading file : " + filename, __CONTEXT__);

                g = iofile::readFile(filename);

                if (algoName == "exact" && g.size() > MAX_EXACT_GRAPH_SIZE) {
                    continue;
                }

                iofile::writeResultFile(outFilename, g, algoName);
            }
        }
    }
}

void runGraphRandomArgs(std::map<std::string, std::vector<std::string>> &args) {
    int n = 1000;
    double p = .5;

    Graph g;

    if (args.find("-n") != args.end() || args.find("--nodes") != args.end()) {
        const std::vector<std::string> nArgs = args.find("-n") != args.end() ? args["-n"] : args["--nodes"];

        n = std::stoi(nArgs[0]);
    }

    if (args.find("-p") != args.end() || args.find("--probability") != args.end()) {
        const std::vector<std::string> pArgs = args.find("-p") != args.end() ? args["-p"] : args["--probability"];

        p = std::stod(pArgs[0]);
    }

    std::string filename;

    g = Graph::createRandomGraph(n, p);

    if (args.find("-o") != args.end() || args.find("--output") != args.end()) {
        const std::vector<std::string> fArgs = args.find("-o") != args.end() ? args["-o"] : args["--output"];

        filename = fArgs[0];
    } else {
        filename = "random_" + std::to_string(n) + "_" + std::to_string(g.m()) + ".in";
    }

    Logger::info("Generated graph with " + std::to_string(n) + " nodes and " + std::to_string(g.m()) + " edges and save it to : " + filename, __CONTEXT__);

    iofile::writeInputFile(filename, g);
}

void runGraphTestAlgo(std::map<std::string, std::vector<std::string>>& args, const std::string& algoName) {

    if (args.find("debug") == args.end()) {
        Logger::setLogLevel(LogLevel::TEST);
    }

    iofile::testAlgo(algoName, args);

}
