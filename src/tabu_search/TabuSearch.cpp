#include "TabuSearch.hpp"

std::pair<int, Partition> TabuSearch_V1::tabuSearch(const Graph &g) {

    if (g.size() % 2 != 0) {
        Logger::error("The number of vertex must be even", __CONTEXT__);
        exit(EXIT_FAILURE);
    }

    auto  [fst, snd] = ConstructiveHeuristic::constructiveHeuristic(g);

    int iterationWithoutUpgrade = 0;

    const int baseCutSize = fst;

    constexpr int maxIteration = MAX_ITERATION;

    while (iterationWithoutUpgrade < maxIteration) {

        // Do random things

        iterationWithoutUpgrade++;

        const int i = rand() % snd.first.size();
        const int j = rand() % snd.second.size();

        std::pair<std::vector<int>, std::vector<int>> newPartition = snd;

        int c = LocalSearch_Utils::optimizeCalculateCutSize(newPartition, g, i, j, fst);

        std::swap(newPartition.first[i], newPartition.second[j]);

        // int c = calculateCutSize(newNewPartition, g);

        TabuSearch_Utils::LocalSearch(newPartition, g, c);

        if (c < fst) {
            fst = c;
            iterationWithoutUpgrade = 0;
            snd = newPartition;
        }

        Logger::debug(LogColor::fgRed + "No upgrade : " + std::to_string(iterationWithoutUpgrade) + LogColor::reset, __CONTEXT__);
    }

    Logger::debug(LogColor::bgBlue + "Size difference : " + std::to_string(baseCutSize - fst) + LogColor::reset, __CONTEXT__);

    return std::make_pair(fst, snd);
}

std::pair<int, Partition> TabuSearch_V2::tabuSearch(const Graph &g) {
    if (g.size() % 2 != 0) {
        Logger::error("The number of vertex must be even", __CONTEXT__);
        exit(EXIT_FAILURE);
    }

    auto  [fst, snd] = ConstructiveHeuristic::constructiveHeuristic(g);

    int currentCutSize = fst;

    auto bestPartition = snd;

    std::vector<TabuMove> tabuList;

    constexpr int maxIterations = 100;
    int iterations = 0;

    constexpr int initialTabuTenure = 10; // Initial tabu tenure
    int currentTabuTenure = initialTabuTenure; // Current tabu tenure

    while (iterations < maxIterations) {

        // swap random vertices
        auto newPartition = bestPartition;

        const int i = rand() % bestPartition.first.size();
        const int j = rand() % bestPartition.second.size();

        int newCutSize = LocalSearch_Utils::optimizeCalculateCutSize(snd, g, i, j, currentCutSize);

        std::swap(newPartition.first[i], newPartition.second[j]);

        if (!isTabuMove(tabuList, newPartition)) {
            TabuSearch_Utils::LocalSearch(newPartition, g, newCutSize);

            if (newCutSize < currentCutSize) {
                currentCutSize = newCutSize;
                bestPartition = newPartition;
                currentTabuTenure = initialTabuTenure;
            } else {
                currentTabuTenure--;
            }

            TabuMove newMove;
            newMove.move = newPartition;
            newMove.iterationsLeft = currentTabuTenure;

            tabuList.push_back(newMove);
        } else {
            Logger::debug("New move is tabu", __CONTEXT__);
        }

        iterations++;

        Logger::debug(LogColor::fgRed + "Iteration : " + std::to_string(iterations) + LogColor::reset, __CONTEXT__);

        // Manage tabu expiration
        for (size_t i = 0; i < tabuList.size(); ++i) {
            tabuList[i].iterationsLeft--;

            // Remove the move from the tabu list if its tenure expires
            if (tabuList[i].iterationsLeft <= 0) {
                tabuList.erase(tabuList.begin() + i);
                i--; // Adjust the index after erasing an element
            }
        }
    }

    Logger::debug("Cut size difference : " + std::to_string(fst - currentCutSize), __CONTEXT__);

    return std::make_pair(currentCutSize, bestPartition);
}

bool TabuSearch_V2::isTabuMove(const std::vector<TabuMove>& tabuList, Partition& move) {
    std::sort(move.first.begin(), move.first.end());
    return std::any_of(tabuList.begin(), tabuList.end(), [&move](const TabuMove& m) { return m.move.first == move.first; });
}

void
TabuSearch_Utils::LocalSearch(std::pair<std::vector<int>, std::vector<int>> &partition, const Graph &g, int &cutSize) {

    int maxIteration = 0;

    bool improvement = true;

    while (improvement) {
        improvement = false;

        for (int i = 0; i < partition.first.size(); i++) {
            const int newCutSize = LocalSearch_Utils::optimizeCalculateCutSize(partition, g, i, i, cutSize);

            if (newCutSize < cutSize) {
                // Logger::debug("Find better solution : " + std::to_string(newCutSize) + " !", __CONTEXT__);

                improvement = true;

                cutSize = newCutSize;

                std::swap(partition.first[i], partition.second[i]);
            }
        }

        maxIteration++;
        // Logger::debug(LogColor::bgRed + "Iteration : " + std::to_string(maxIteration) + LogColor::reset, __CONTEXT__);

        if (maxIteration == 500) {
            // maxIteration will break the loop
            Logger::debug("LocalSearch algorithm max iteration reached", __CONTEXT__);
            break;
        }
    }
}