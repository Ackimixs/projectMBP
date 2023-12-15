#include "iofile.hpp"

Graph iofile::readFile(const std::string &filename) {

    Logger::info("reading file : " + filename, __CONTEXT__);

    std::ifstream inputFile(filename);

    if (inputFile.is_open()) {

        std::string line;

        std::getline(inputFile, line);

        std::istringstream iss(line);

        int n, m;

        iss >> n >> m;

        if (n % 2 != 0) {
            Logger::error("The number of vertex must be even", __CONTEXT__);
            exit(EXIT_FAILURE);
        }

        Graph g(n);

        std::getline(inputFile, line);

        std::istringstream listOfEdge(line);

        int v1, v2;

        while (listOfEdge >> v1 >> v2) {
            g.addEdge(v1, v2);

            listOfEdge.ignore(2, ' ');
        }

        Logger::info("Graph created, size : " + std::to_string(g.size()) + " m : " + std::to_string(g.m()), __CONTEXT__);

        return g;
    } else {
        Logger::error("Unable to open file " + filename, __CONTEXT__);
        exit(EXIT_FAILURE);
    }
}

void iofile::writeResultFile(const std::string& filename, const Graph& g, const std::string& algoName) {

    Logger::info("Writing to file : " + filename + " running " + LogColor::fgRed + algoName + LogColor::reset + " algorithm", __CONTEXT__);

    // ALGO RUNNER PART
    std::pair<int, Partition> t;

    std::pair<int, Partition> (*algo)(const Graph&);

    if (algoName == "exact") {
        algo = Exact::exactAlgorithm;
    } else if (algoName == "constructive") {
        algo = ConstructiveHeuristic::constructiveHeuristic;
    } else if (algoName == "local_search") {
        algo = LocalSearch::localSearch;
    } else if (algoName == "tabu_search") {
        algo = TabuSearch::tabuSearch;
    } else {
        Logger::error("No algo named : " + algoName, __CONTEXT__);
        exit(EXIT_FAILURE);
    }

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    t = algo(g);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();

    Logger::info(LogColor::fgRed + algoName + LogColor::reset + " algorithm result : " + LogColor::fgBrightRed + std::to_string(t.first) + LogColor::reset + " vertex between the two sets", __CONTEXT__);

    Logger::info("Time taken by " + LogColor::fgRed + algoName + LogColor::reset + " algorithm is : " + LogColor::fgBrightRed + std::to_string(time) + LogColor::reset + " ns", __CONTEXT__);

    std::ofstream outputFile(filename);

    if (outputFile.is_open()) {

        // WRITING PART

        std::vector<int> v1 = t.second.first;

        std::vector<int> v2 = t.second.second;

        int vertexBetweenSet = t.first;

        outputFile << g.size() << " " << vertexBetweenSet << "\n";

        for (int v : v1) {
            outputFile << v << " ";
        }
        outputFile << "\n";
        for (int v : v2) {
            outputFile << v << " ";
        }
        outputFile << "\n";

    } else {
        Logger::error("Unable to open file " + filename, __CONTEXT__);
        exit(EXIT_FAILURE);
    }
}

void iofile::writeInputFile(const std::string &filename, const Graph &g) {

    Logger::debug("Writing to file : " + filename, __CONTEXT__);

    std::ofstream outputFile(filename);

    if (outputFile.is_open()) {

        outputFile << g.size() << " " << g.m() << "\n";

        for (int i = 0; i < g.size(); i++) {
            for (const int j : g.successor(i)) {
                outputFile << i << " " << j << "  ";
            }
        }

    } else {
        Logger::error("Unable to open file " + filename, __CONTEXT__);
        exit(EXIT_FAILURE);
    }
}

void iofile::testAlgo(const std::string& algoName, std::map<std::string, std::vector<std::string>>& args) {

    std::pair<int, Partition> (*algo)(const Graph&);
    std::vector<int> prob;
    std::vector<int> size;

    unsigned int nbTest;

    if (args.find("-p") != args.end() || args.find("--prob") != args.end()) {
        std::vector<std::string> probArgs = args.find("-p") != args.end() ? args["-p"] : args["--prob"];
        for (const std::string& p : probArgs) {
            prob.push_back(std::stoi(p));
        }
    } else {
        prob = {25, 50, 75};
    }

    if (args.find("-s") != args.end() || args.find("--size") != args.end()) {
        std::vector<std::string> sizeArgs = args.find("-s") != args.end() ? args["-s"] : args["--size"];
        for (const std::string& s : sizeArgs) {
            size.push_back(std::stoi(s));
        }
    } else {
        size = {10, 20, 30};
    }

    if (args.find("--repeat") != args.end()) {
        nbTest = std::stoi(args["--repeat"][0]);
    } else {
        nbTest = 10;
    }

    if (algoName == "exact") {
        algo = Exact::exactAlgorithm;
    } else if (algoName == "constructive") {
        algo = ConstructiveHeuristic::constructiveHeuristic;
    } else if (algoName == "local_search") {
        algo = LocalSearch::localSearch;
    } else if (algoName == "tabu_search") {
        algo = TabuSearch::tabuSearch;
    } else {
        Logger::error("No algo named : " + algoName, __CONTEXT__);
        exit(EXIT_FAILURE);
    }

    for (int p : prob) {

        std::ofstream outputFile("../report/data/" + algoName + "_" + std::to_string(p) + ".dat");

        for (int i : size) {

            long totalTime = 0;

            for (int k = 0; k < nbTest; k++) {
                Graph g = Graph::createRandomGraph(i, p / 100.0);

                std::pair<int, Partition> part;

                std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

                part = algo(g);

                std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

                auto micros = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();

                auto sec = std::chrono::duration_cast<std::chrono::seconds>(end - begin).count();

                Logger::info(LogColor::fgRed + algoName + LogColor::reset + " algorithm result : " + LogColor::fgBrightRed + std::to_string(part.first) + LogColor::reset + " vertex between the two sets. the Algorithm took " + std::to_string(micros) + " micro s = " + std::to_string(sec) + " s", __CONTEXT__);

                totalTime += micros;

            }

            totalTime /= nbTest;

            outputFile << i << " " << totalTime << "\n";
        }

        outputFile.close();
    }

}
