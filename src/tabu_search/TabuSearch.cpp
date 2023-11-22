#include "TabuSearch.hpp"

std::pair<int, Partition> TabuSearch_V1::tabuSearch(const Graph &g) {

    if (g.size() % 2 != 0) {
        Logger::error("The number of vertex must be even", __CONTEXT__);
        exit(EXIT_FAILURE);
    }

    std::pair<int, Partition> res = ConstructiveHeuristic::constructiveHeuristic(g);

    int iterationWithoutUpgrade = 0;

    int cutSize = res.first;

    int baseCutSize = cutSize;

    int maxIteration = 70;

    while (iterationWithoutUpgrade < maxIteration) {

        // Do random things

        iterationWithoutUpgrade++;

        int i = rand() % res.second.first.size();
        int j = rand() % res.second.second.size();

        std::pair<std::vector<int>, std::vector<int>> newNewPartition = res.second;

        std::swap(newNewPartition.first[i], newNewPartition.second[j]);

//        int newCutSize = optimizeCalculateCutSize(newNewPartition, g, i, j, cutSize);
        int c = calculateCutSize(newNewPartition, g);

        LocalSearch(newNewPartition, g, c);

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

void
TabuSearch_V1::LocalSearch(std::pair<std::vector<int>, std::vector<int>> &partition, const Graph &g, int &cutSize) {

    int maxIteration = 0;

    bool improvement = true;

    while (improvement) {

        improvement = false;

        for (int k = 0; k < partition.first.size(); k++) {
            std::swap(partition.first[k], partition.second[k]);

            int newCutSize = LocalSearch_Utils::optimizeCalculateCutSize(partition, g, k, k, cutSize);

            if (newCutSize < cutSize) {
                Logger::debug("Find better solution : " + std::to_string(newCutSize) + " !", __CONTEXT__);

                improvement = true;
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