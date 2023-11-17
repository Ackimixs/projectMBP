#include "iofile.hpp"

Graph iofile::readFile(const std::string &filename) {

    Logger::info("reading file : " + filename + ".in", __CONTEXT__);

    std::ifstream inputFile(filename + ".in");

    if (inputFile.is_open()) {

        std::string line;

        std::getline(inputFile, line);

        std::istringstream iss(line);

        int n, m;

        iss >> n >> m;

        if (n % 2 != 0) {
            Logger::error("The number of vertex must be even", __CONTEXT__);
            exit(1);
        }

        Graph g(n);

        std::getline(inputFile, line);

        std::istringstream listOfEdge(line);

        int v1, v2;

        while (listOfEdge >> v1 >> v2) {
            g.addEdge(v1, v2);

            listOfEdge.ignore(2, ' ');
        }

        return g;
    } else {
        Logger::error("Unable to open file " + filename, __CONTEXT__);
        exit(1);
    }
}

void iofile::writeResultFile(const std::string& filename, const Graph& g, const std::string& algoName) {

    // ALGO RUNNER PART
    std::pair<int, Partition> t;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    if (algoName == "exact") {
        t = exact_V2::exactAlgorithm(g);
    } else if (algoName == "exact_v1") {
        t = exact_V1::exactAlgorithm(g);
    } else if (algoName == "constructive") {
        t = ConstructiveHeuristic_V1::constructiveHeuristic(g);
    } else if (algoName == "constructive_v4") {
        t = ConstructiveHeuristic_V4::constructiveHeuristic(g);
    } else {
        Logger::error("No algo named : " + algoName, __CONTEXT__);
        exit(-1);
    }

    Logger::info(LogColor::fgRed + algoName + LogColor::reset + " algorithm result : " + LogColor::fgBrightRed + std::to_string(t.first) + LogColor::reset + " vertex between the two sets", __CONTEXT__);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

    Logger::info("Time taken by " + LogColor::fgRed + algoName + LogColor::reset + " algorithm is : " + LogColor::fgBrightRed + std::to_string(time) + LogColor::reset + " ms", __CONTEXT__);

    Logger::info("Writing to file : " + filename + "_" + algoName + ".out running " + LogColor::fgRed + algoName + LogColor::reset + " algorithm", __CONTEXT__);

    std::ofstream outputFile(filename + "_" + algoName + ".out");

    if (outputFile.is_open()) {

        // WRITING PART

        std::unordered_set<int> v1 = t.second.first;

        std::unordered_set<int> v2 = t.second.second;

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
        exit(1);
    }
}

void iofile::writeInputFile(const std::string &filename, const Graph &g) {

    Logger::debug("Writing to file : " + filename + ".in", __CONTEXT__);

    std::ofstream outputFile(filename + ".in");

    if (outputFile.is_open()) {

        outputFile << g.size() << " " << g.m() << "\n";

        for (int i = 0; i < g.size(); i++) {
            for (int j : g.directed(i)) {
                outputFile << i << " " << j << "  ";
            }
        }

    } else {
        Logger::error("Unable to open file " + filename, __CONTEXT__);
        exit(1);
    }
}