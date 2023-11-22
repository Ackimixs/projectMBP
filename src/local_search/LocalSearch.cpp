#include "LocalSearch.hpp"

std::pair<int, Partition> LocalSearch_V1::localSearch(const Graph &g) {
    if (g.size() % 2 != 0) {
        Logger::error("The number of vertex must be even", __CONTEXT__);
        exit(EXIT_FAILURE);
    }

    std::pair<int, Partition> initialSolutionSet = ConstructiveHeuristic::constructiveHeuristic(g);

    Partition newPartition = initialSolutionSet.second;

    int cutSize = initialSolutionSet.first;

    int beforeCutSize = __INT_MAX__;

    int maxIteration = 0;

    while (cutSize < beforeCutSize) {
        beforeCutSize = cutSize;
        for (int k = 0; k < newPartition.first.size(); k++) {
            std::swap(newPartition.first[k], newPartition.second[k]);

            int newCutSize = LocalSearch_Utils::optimizeCalculateCutSize(newPartition, g, k, k, cutSize);

            if (newCutSize < cutSize) {
                Logger::debug("Find better solution : " + std::to_string(newCutSize) + " !", __CONTEXT__);

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

    initialSolutionSet.second = newPartition;

    initialSolutionSet.first = cutSize;

    return initialSolutionSet;
}

std::pair<int, Partition> LocalSearch_V2::localSearch(const Graph &g) {
    if (g.size() % 2 != 0) {
        Logger::error("The number of vertex must be even", __CONTEXT__);
        exit(EXIT_FAILURE);
    }

    std::pair<int, Partition> initialSolutionSet = ConstructiveHeuristic::constructiveHeuristic(g);

    Partition newPartition = initialSolutionSet.second;

    int cutSize = initialSolutionSet.first;

    int beforeCutSize = __INT_MAX__;

    int maxIteration = 0;

    while (cutSize < beforeCutSize) {
        beforeCutSize = cutSize;

        for (int k = 0; k < newPartition.first.size(); k++) {
            for (int i = 0; i < newPartition.second.size(); i++) {
                std::swap(newPartition.first[k], newPartition.second[i]);

                int newCutSize = LocalSearch_Utils::optimizeCalculateCutSize(newPartition, g, k, i, cutSize);

                if (newCutSize < cutSize) {
                    Logger::debug("Find better solution : " + std::to_string(newCutSize) + " !", __CONTEXT__);

                    cutSize = newCutSize;
                } else {
                    std::swap(newPartition.first[k], newPartition.second[i]);
                }
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

    initialSolutionSet.second = newPartition;

    initialSolutionSet.first = cutSize;

    return initialSolutionSet;
}

std::pair<int, Partition> LocalSearch_V3::localSearch(const Graph &g) {
    if (g.size() % 2 != 0) {
        Logger::error("The number of vertex must be even", __CONTEXT__);
        exit(EXIT_FAILURE);
    }

    std::pair<int, Partition> initialSolutionSet = ConstructiveHeuristic::constructiveHeuristic(g);

    Partition newPartition = initialSolutionSet.second;

    int cutSize = initialSolutionSet.first;

    int maxIteration = 0;

    bool improvement = true;

    while (improvement) {
        improvement = false;

        for (int i = 0; i < newPartition.first.size(); i++) {
            std::swap(newPartition.first[i], newPartition.second[i]);

            int newCutSize = LocalSearch_Utils::optimizeCalculateCutSize(newPartition, g, i, i, cutSize);

            if (newCutSize < cutSize) {
                Logger::debug("Find better solution : " + std::to_string(newCutSize) + " !", __CONTEXT__);

                improvement = true;
                cutSize = newCutSize;
            } else {
                std::swap(newPartition.first[i], newPartition.second[i]);
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

    initialSolutionSet.second = newPartition;

    initialSolutionSet.first = cutSize;

    return initialSolutionSet;
}

int
LocalSearch_Utils::optimizeCalculateCutSize(std::pair<std::vector<int>, std::vector<int>> partition, const Graph &graph,
                                            int firstIndex, int secondIndex, int actualCutSize) {
    // That cut size is a particular case of the calculateCutSize function, it calculates the cut size of the graph for a swap of two vertexes

    // swap has already been done
    int newCutSize = actualCutSize;

    std::swap(partition.first[firstIndex], partition.second[secondIndex]);

    for (auto v : partition.second) {
        if (graph.isEdge(partition.first[firstIndex], v)) {
            newCutSize--;
        }
    }

    for (auto v : partition.first) {
        if (graph.isEdge(partition.second[secondIndex], v)) {
            newCutSize--;
        }
    }

    std::swap(partition.first[firstIndex], partition.second[secondIndex]);

    for (auto v : partition.second) {
        if (graph.isEdge(partition.first[firstIndex], v)) {
            newCutSize++;
        }
    }

    for (auto v : partition.first) {
        if (graph.isEdge(partition.second[secondIndex], v)) {
            newCutSize++;
        }
    }
    return newCutSize;
}