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

        LocalSearch::mainLocalSearch(newPartition, c, g);

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

    const unsigned int maxIterations = g.size() / 4;
    const unsigned int maxIterationsWithoutUpgrade = g.size() / 10;
    int iterations = 0;
    int it2 = 0;

    constexpr int initialTabuTenure = 10; // Initial tabu tenure
    int currentTabuTenure = initialTabuTenure; // Current tabu tenure

    while (iterations < maxIterations && it2 < maxIterationsWithoutUpgrade) {

        // swap random vertices
        auto newPartition = bestPartition;

        const int i = rand() % bestPartition.first.size();
        const int j = rand() % bestPartition.second.size();

        int newCutSize = LocalSearch_Utils::optimizeCalculateCutSize(newPartition, g, i, j, currentCutSize);

        std::swap(newPartition.first[i], newPartition.second[j]);

        if (!isTabuMove(tabuList, i, j)) {
            auto [a, b] = LocalSearch::mainLocalSearch(newPartition, newCutSize, g);

            if (a < currentCutSize) {
                currentCutSize = a;
                bestPartition = b;
                currentTabuTenure = initialTabuTenure;
                it2 = 0;
            } else {
                currentTabuTenure--;
            }

            TabuMove newMove{};
            newMove.index = {i, j};
            newMove.iterationsLeft = currentTabuTenure;

            tabuList.push_back(newMove);
        } else {
            Logger::debug("New move is tabu", __CONTEXT__);
        }

        iterations++;
        it2++;

        Logger::debug(LogColor::fgRed + "Iteration : " + std::to_string(iterations) + LogColor::reset, __CONTEXT__);

        // Manage tabu expiration
        for (size_t k = 0; k < tabuList.size(); ++k) {
            tabuList[k].iterationsLeft--;

            // Remove the move from the tabu list if its tenure expires
            if (tabuList[k].iterationsLeft <= 0) {
                tabuList.erase(tabuList.begin() + k);
                k--; // Adjust the index after erasing an element
            }
        }
    }

    Logger::debug("Cut size difference : " + std::to_string(fst - currentCutSize), __CONTEXT__);

    return std::make_pair(currentCutSize, bestPartition);
}

bool TabuSearch_V2::isTabuMove(const std::vector<TabuMove>& tabuList, const int firstIndex, const int secondIndex) {
    return std::any_of(tabuList.begin(), tabuList.end(), [&firstIndex, &secondIndex](const TabuMove& m) { return (m.index.firstIndex == firstIndex && m.index.secondIndex == secondIndex); });
}
