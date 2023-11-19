#pragma once

#include "../model/Graph.hpp"

#include "../constructive/ConstructiveHeuristic.hpp"

namespace TabuSearch_V1 {
    std::pair<int, Partition> tabuSearch(const Graph& g);

    void LocalSearch(std::pair<std::vector<int>, std::vector<int>> &partition, const Graph &g, int &cutSize);

    int optimizeCalculateCutSize(std::pair<std::vector<int>, std::vector<int>> partition, const Graph &graph,
                                 int firstIndex, int secondIndex, int actualCutSize);
}

namespace TabuSearch = TabuSearch_V1;