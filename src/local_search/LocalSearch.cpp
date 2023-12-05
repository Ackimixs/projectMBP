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

            const int newCutSize = LocalSearch_Utils::optimizeCalculateCutSize(newPartition, g, k, k, cutSize);

            if (newCutSize < cutSize) {
                Logger::debug("Find better solution : " + std::to_string(newCutSize) + " !", __CONTEXT__);
  
                std::swap(newPartition.first[k], newPartition.second[k]);

                cutSize = newCutSize;
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
                const int newCutSize = LocalSearch_Utils::optimizeCalculateCutSize(newPartition, g, k, i, cutSize);

                if (newCutSize < cutSize) {
                    Logger::debug("Find better solution : " + std::to_string(newCutSize) + " !", __CONTEXT__);

                    std::swap(newPartition.first[k], newPartition.second[i]);

                    cutSize = newCutSize;
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
            const int newCutSize = LocalSearch_Utils::optimizeCalculateCutSize(newPartition, g, i, i, cutSize);

            if (newCutSize < cutSize) {
                Logger::debug("Find better solution : " + std::to_string(newCutSize) + " !", __CONTEXT__);

                improvement = true;

                cutSize = newCutSize;

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
LocalSearch_Utils::optimizeCalculateCutSize(const std::pair<std::vector<int>, std::vector<int>>& partition, const Graph &graph,
                                            const int firstIndex, const int secondIndex, int actualCutSize) {
    const int firstVertex = partition.first[firstIndex];
    const int secondVertex = partition.second[secondIndex];

    for (const auto v : partition.second) {
        if (v == firstVertex || v == secondVertex) {
            continue;
        }

        if (graph.isEdge(firstVertex, v)) {
            actualCutSize--;
        }

        if (graph.isEdge(secondVertex, v)) {
            actualCutSize++;
        }
    }

    for (const auto v : partition.first) {
        if (v == firstVertex || v == secondVertex) {
            continue;
        }

        if (graph.isEdge(secondVertex, v)) {
            actualCutSize--;
        }

        if (graph.isEdge(firstVertex, v)) {
            actualCutSize++;
        }
    }

    return actualCutSize;
}

std::pair<int, Partition> LocalSearch_V4::localSearch(const Graph &g) {
    if (g.size() % 2 != 0) {
        Logger::error("The number of vertex must be even", __CONTEXT__);
        exit(EXIT_FAILURE);
    }

    std::pair<int, Partition> initialSolutionSet = ConstructiveHeuristic::constructiveHeuristic(g);

    Logger::debug("Local search - solution find by constructive heuristic : " + std::to_string(initialSolutionSet.first), __CONTEXT__);

    Partition newPartition = initialSolutionSet.second;

    int cutSize = initialSolutionSet.first;

    int candidateCutSize = cutSize;

    std::pair<int, int> candidateIndexes;

    int maxIteration = 0;

    bool improvement = true;

    while (improvement) {
        improvement = false;

        // Make an iteration to every vertex and get the best
        for (int i = 0; i < newPartition.first.size(); i++) {
            for (int k = 0; k < newPartition.second.size(); k++) {
                const int newCutSize = LocalSearch_Utils::optimizeCalculateCutSize(newPartition, g, i, k, cutSize);

                if (newCutSize < candidateCutSize) {
                    Logger::debug("Find better solution : " + std::to_string(newCutSize) + " !", __CONTEXT__);

                    improvement = true;

                    candidateIndexes = std::make_pair(i, k);

                    candidateCutSize = newCutSize;
                }
            }
        }

        if (improvement) {
            std::swap(newPartition.first[candidateIndexes.first], newPartition.second[candidateIndexes.second]);
            cutSize = candidateCutSize;
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

std::pair<int, Partition> LocalSearch_V5::localSearch(const Graph &g) {
    if (g.size() % 2 != 0) {
        Logger::error("The number of vertex must be even", __CONTEXT__);
        exit(EXIT_FAILURE);
    }

    std::pair<int, Partition> initialSolutionSet = ConstructiveHeuristic::constructiveHeuristic(g);

    Logger::debug("Local search - solution find by constructive heuristic : " + std::to_string(initialSolutionSet.first), __CONTEXT__);

    Partition newPartition = initialSolutionSet.second;

    int cutSize = initialSolutionSet.first;

    int maxIteration = 0;

    bool improvement = true;

    while (improvement) {
        improvement = false;

        // Make an iteration to every vertex and get the best
        for (int i = 0; i < newPartition.first.size(); i++) {
            for (int k = 0; k < newPartition.second.size(); k++) {
                const int newCutSize = LocalSearch_Utils::optimizeCalculateCutSize(newPartition, g, i, k, cutSize);

                if (newCutSize < cutSize) {
                    Logger::debug("Find better solution : " + std::to_string(newCutSize) + " !", __CONTEXT__);

                    improvement = true;

                    std::swap(newPartition.first[i], newPartition.second[k]);
                    cutSize = newCutSize;

                    // Break the inner loop as soon as a better solution is found
                    break;
                }
            }

            // If a better solution was found, break the outer loop as well
            if (improvement) {
                break;
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