#pragma once

#include "../local_search/LocalSearch.hpp"

struct TabuMove {
    struct
    {
        int firstIndex;
        int secondIndex;
    } index;
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

    bool isTabuMove(const std::vector<TabuMove>& tabuList, const int firstIndex, const int secondIndex);
}

namespace TabuSearch = TabuSearch_V2;