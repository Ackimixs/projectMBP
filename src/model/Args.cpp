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

void runGraphAlgoArgs(std::map<std::string, std::vector<std::string>> &args, const std::string& algoName) {
    Graph g;

    // TODO usage : if algoName = "all" then run all algo in the folder instance/<algo_name> and save the result in ./result/<algo_name>

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

                if (g.size() < 30) {
                    iofile::writeResultFile(outFilename, g, "exact");
                }

                outFilename = "../results/constructive/" + entry.path().filename().string();

                iofile::writeResultFile(outFilename, g, "constructive");

                outFilename = "../results/local_search/" + entry.path().filename().string();

                iofile::writeResultFile(outFilename, g, "local_search");

                outFilename = "../results/tabu_search/" + entry.path().filename().string();

                iofile::writeResultFile(outFilename, g, "tabu_search");
            }
        } else {
            for (const auto &entry : std::filesystem::directory_iterator("../instances/" + algoName)) {
                std::string filename = entry.path().string();

                std::string outFilename = "../results/" + algoName + "/" + entry.path().filename().string();

                Logger::debug("Reading file : " + filename, __CONTEXT__);

                g = iofile::readFile(filename);

                if (algoName == "exact" && g.size() > 30) {
                    continue;
                }

                iofile::writeResultFile(filename, g, algoName);
            }
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

    if (args.find("-o") != args.end() || args.find("--output") != args.end()) {
        std::vector<std::string> fArgs = args.find("-o") != args.end() ? args["-o"] : args["--output"];

        filename = fArgs[0];
    } else {
        filename = "random_" + std::to_string(n) + "_" + std::to_string(p) + ".in";
    }

    Logger::debug("Generating graph with " + std::to_string(n) + " nodes and " + std::to_string(p) + " probability and save it to : " + filename, __CONTEXT__);

    g = Graph::createRandomGraph(n, p);
    iofile::writeInputFile(filename, g);
}