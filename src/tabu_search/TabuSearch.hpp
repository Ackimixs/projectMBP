#pragma once

#include "../local_search/LocalSearch.hpp"

struct TabuMove {
    Partition move;
    int iterationsLeft;
};

/**
 * \brief break;
 */
namespace TabuSearch_V1 {
    std::pair<int, Partition> tabuSearch(const Graph& g);
}

namespace TabuSearch_V2 {
    std::pair<int, Partition> tabuSearch(const Graph& g);

    bool isTabuMove(const std::vector<TabuMove>& tabuList, Partition& move);
}

namespace TabuSearch_Utils {
    void LocalSearch(std::pair<std::vector<int>, std::vector<int>> &partition, const Graph &g, int &cutSize);

    void LocalSearch_V2(std::pair<std::vector<int>, std::vector<int>> &partition, const Graph &g, int &cutSize);
}

namespace TabuSearch = TabuSearch_V2;