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
}

/**
 * result : better result but more time complexity (7118 for him and 7255 for the first)
 * but 379ms for it and 8ms for the first
 * that return the real value
 * So that is a real heuristic algorithm
 */
namespace LocalSearch_V2 {
    std::pair<int, Partition> localSearch(const Graph& g);
}


/**
 * exactly the same as the first algorithm with a little change on the stop criteria
 * result : time execution is a little smaller than the first so we will use it
 */
namespace LocalSearch_V3 {
    std::pair<int, Partition> localSearch(const Graph& g);
}

namespace LocalSearch_Utils {
    int optimizeCalculateCutSize(std::pair<std::vector<int>, std::vector<int>> partition, const Graph &graph, int firstIndex, int secondIndex,
                                 int actualCutSize);
}

/**
 * the good local search is the first
 */
namespace LocalSearch = LocalSearch_V1;