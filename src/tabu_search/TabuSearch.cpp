#include "TabuSearch.hpp"

std::pair<int, Partition> TabuSearch_V1::tabuSearch(const Graph &g) {

    if (g.size() % 2 != 0) {
        Logger::error("The number of vertex must be even", __CONTEXT__);
        exit(EXIT_FAILURE);
    }

    std::pair<int, Partition> res = ConstructiveHeuristic::constructiveHeuristic(g);

    std::pair<std::vector<int>, std::vector<int>> newPartition = std::make_pair(std::vector<int>(res.second.first.begin(), res.second.first.end()),
                                                                                std::vector<int>(res.second.second.begin(), res.second.second.end()));

    int iterationWithoutUpgrade = 0;

    int cutSize = res.first;

    int baseCutSize = cutSize;

    int maxIteration = 100;

    while (iterationWithoutUpgrade < maxIteration) {

        // Do random things

        iterationWithoutUpgrade++;

        int i = rand() % newPartition.first.size();
        int j = rand() % newPartition.second.size();

        std::pair<std::vector<int>, std::vector<int>> newNewPartition = newPartition;

        std::swap(newNewPartition.first[i], newNewPartition.second[j]);

        LocalSearch(newNewPartition, g);

        int newCutSize = calculateCutSize(newNewPartition, g);

        if (newCutSize < cutSize) {
            cutSize = newCutSize;
            iterationWithoutUpgrade = 0;
            newPartition = newNewPartition;
        }

        Logger::debug(LogColor::fgRed + "No upgrade : " + std::to_string(iterationWithoutUpgrade) + LogColor::reset, __CONTEXT__);
    }

    Logger::debug(LogColor::bgBlue + "Size difference : " + std::to_string(baseCutSize - cutSize) + LogColor::reset, __CONTEXT__);

    return std::make_pair(cutSize, Partition(std::unordered_set<int>(newPartition.first.begin(), newPartition.first.end()),
                                              std::unordered_set<int>(newPartition.second.begin(), newPartition.second.end())));
}

void TabuSearch_V1::LocalSearch(std::pair<std::vector<int>, std::vector<int>> &partition, const Graph &g) {
    // Do one itération of local search

    int cutSize = calculateCutSize(partition, g);

    int beforeCutSize = __INT_MAX__;

    int maxIteration = 0;

    while (cutSize < beforeCutSize) {
        beforeCutSize = cutSize;
        for (int k = 0; k < partition.first.size(); k++) {
            std::swap(partition.first[k], partition.second[k]);

            int newCutSize = optimizeCalculateCutSize(partition, g, k, cutSize);

            if (newCutSize < cutSize) {
                Logger::debug("Find better solution : " + std::to_string(newCutSize) + " !", __CONTEXT__);

                cutSize = newCutSize;
            } else {
                std::swap(partition.first[k], partition.second[k]);
            }
        }

        maxIteration++;
        Logger::debug(LogColor::bgRed + "Iteration : " + std::to_string(maxIteration) + LogColor::reset, __CONTEXT__);

        if (maxIteration == 500) {
            // maxIteration will break the loop
            Logger::debug("LocalSearch algorithm max iteration reached", __CONTEXT__);
            break;
        }
    }
}

int
TabuSearch_V1::optimizeCalculateCutSize(std::pair<std::vector<int>, std::vector<int>> partition, const Graph &graph,
                                         int index,
                                         int actualCutSize) {
    // That cut size is a particular case of the calculateCutSize function, it calculates the cut size of the graph for a swap of two vertexes

    int newCutSize = actualCutSize;

    std::swap(partition.first[index], partition.second[index]);

    for (auto v : partition.second) {
        if (graph.isEdge(partition.first[index], v)) {
            newCutSize--;
        }
    }

    for (auto v : partition.first) {
        if (graph.isEdge(partition.second[index], v)) {
            newCutSize--;
        }
    }

    std::swap(partition.first[index], partition.second[index]);

    for (auto v : partition.second) {
        if (graph.isEdge(partition.first[index], v)) {
            newCutSize++;
        }
    }

    for (auto v : partition.first) {
        if (graph.isEdge(partition.second[index], v)) {
            newCutSize++;
        }
    }
    return newCutSize;
}