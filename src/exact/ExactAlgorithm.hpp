#pragma once

#include "../model/Graph.hpp"

namespace exact_V1 {
    std::pair<int, Partition> exactAlgorithm(const Graph& g);
    std::vector<std::vector<int>> getAllPair(int n);
    void generateCombinations(std::vector<int>& currentCombination, int start, int n, int k, std::vector<std::vector<int>>& result);
}

namespace exact_V2 {
    std::pair<int, Partition> exactAlgorithm(const Graph& g);

    int calculateCutSize(const Partition &partition, const Graph& graph);

    void explorePartitions(Partition &partition, int vertex, int &minCut, Partition &minPartition, const Graph &graph);
}