#pragma once

#include "../model/Graph.hpp"

namespace exact_V1 {
    std::pair<int, Partition> exactAlgorithm(const Graph& g);
    std::vector<std::vector<int>> getAllPair(int n);
    void generateCombinations(std::vector<int>& currentCombination, int start, int n, int k, std::vector<std::vector<int>>& result);
}

/**
 * idea : take the first algorithm but upgrade it by checking every time the bisection and if bigger stop
 *
 * result :s
 * That work but i don't think that work (see the onenote for more)
 * Take minus time when the graph has not a big number of edge, when the graph has a lot there is more things to check
 * and the the stop condition of the tree recursion is not often reached because the time that there is more edge is
 * when the two set are almost full.
 */
namespace exact_V2 {
    std::pair<int, Partition> exactAlgorithm(const Graph& g);

    bool checkPartition(const Graph &g, int &partSize, std::unordered_set<int> set);

    void checkAllPair(const Graph &g, Partition &part, int &partSize, std::unordered_set<int> set, int n, int start, int k = 2);
}