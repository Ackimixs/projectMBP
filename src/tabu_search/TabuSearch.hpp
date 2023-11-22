#pragma once

#include "../local_search/LocalSearch.hpp"

namespace TabuSearch_V1 {
    std::pair<int, Partition> tabuSearch(const Graph& g);

    void LocalSearch(std::pair<std::vector<int>, std::vector<int>> &partition, const Graph &g, int &cutSize);
}

namespace TabuSearch = TabuSearch_V1;