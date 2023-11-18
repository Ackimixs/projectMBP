#include "LocalSearch.hpp"

std::pair<int, Partition> LocalSearch_V1::localSearch(const Graph &g) {

    if (g.size() % 2 != 0) {
        Logger::error("The number of vertex must be even", __CONTEXT__);
        exit(EXIT_FAILURE);
    }

    std::pair<int, Partition> initialSolutionSet = ConstructiveHeuristic::constructiveHeuristic(g);

    std::pair<std::vector<int>, std::vector<int>> newPartition = std::make_pair(std::vector<int>(initialSolutionSet.second.first.begin(), initialSolutionSet.second.first.end()),
                                                                                std::vector<int>(initialSolutionSet.second.second.begin(), initialSolutionSet.second.second.end()));

    int cutSize = initialSolutionSet.first;

    int beforeCutSize = __INT_MAX__;

    int maxIteration = 0;

    while (cutSize < beforeCutSize) {
        beforeCutSize = cutSize;
        for (int k = 0; k < newPartition.first.size(); k++) {
            std::swap(newPartition.first[k], newPartition.second[k]);

            int newCutSize = optimizeCalculateCutSize(newPartition, g, k, cutSize);

            if (newCutSize < cutSize) {
//                Logger::debug("Find better solution : " + std::to_string(newCutSize) + " !", __CONTEXT__);

                cutSize = newCutSize;
            } else {
                std::swap(newPartition.first[k], newPartition.second[k]);
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

    Logger::debug("Max iteration : " + std::to_string(maxIteration), __CONTEXT__);

    initialSolutionSet.second.first = std::unordered_set<int>(newPartition.first.begin(), newPartition.first.end());

    initialSolutionSet.second.second = std::unordered_set<int>(newPartition.second.begin(), newPartition.second.end());

    initialSolutionSet.first = cutSize;

    int t = calculateCutSize(initialSolutionSet.second, g);

    Logger::debug("Cut size : " + std::to_string(t), __CONTEXT__);
    Logger::debug("Size of first partition : " + std::to_string(initialSolutionSet.second.first.size()), __CONTEXT__);
    Logger::debug("Size of second partition : " + std::to_string(initialSolutionSet.second.second.size()), __CONTEXT__);

    return initialSolutionSet;
}

int
LocalSearch_V1::optimizeCalculateCutSize(std::pair<std::vector<int>, std::vector<int>> partition, const Graph &graph,
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