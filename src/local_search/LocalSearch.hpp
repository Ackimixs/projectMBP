#pragma once

#include "../constructive/ConstructiveHeuristic.hpp"

/**
 * think this algo look good but constructive heuristic is not good enough
 *
 * stop condition => when the cut size is not better
 * neighbor solution : swap the two vertex with the same index in the two partition (maybe change it for the v2 because this is expensive in complexity)
 */
namespace LocalSearch_V1 {

    std::pair<int, Partition> localSearch(const Graph& g);

    int
    optimizeCalculateCutSize(std::pair<std::vector<int>, std::vector<int>> partition, const Graph &graph, int index,
                             int actualCutSize);

}