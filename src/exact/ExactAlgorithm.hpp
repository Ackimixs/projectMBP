#pragma once

#include "../model/Graph.hpp"

namespace Exact_V1 {
    std::pair<int, Partition> exactAlgorithm(const Graph& g);
    std::vector<std::vector<int>> getAllPair(int n);
    void generateCombinations(std::vector<int>& currentCombination, int start, int n, int k, std::vector<std::vector<int>>& result);
}

/**
 * idea : take the first algorithm but upgrade it by checking every time the bisection and if bigger stop
 *
 * result :
 * That maybe work fine
 * Take minus time when the graph has not a big number of edge, when the graph has a lot there is more things to check
 * and the the stop condition of the tree recursion is not often reached because the time that there is more edge is
 * when the two set are almost full.
 */
namespace Exact_V2 {
    std::pair<int, Partition> exactAlgorithm(const Graph& g);

    bool checkPartition(const Graph &g, int &partSize, std::vector<int> vec);

    void checkAllPair(const Graph &g, Partition &part, int &partSize, std::vector<int> vector, int n, int start, int k = 2);
}

/**
 * the good exact algorithm is the second
 */
namespace Exact = Exact_V1;