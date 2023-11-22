#pragma once

#include "../model/Graph.hpp"

#include <unordered_set>

/**
 * LETS FUCKING GO
 * Work fine for a minimum size of edge
 * With 1000 vertex and 10000 edge that work well but
 * when 1000 vertex and 100000 edge that do not work partition size (40 -- 960)
 *
 * NOT GOOD ENOUGH (so idk if i have to upgrade it)
 */
namespace ConstructiveHeuristic_V1 {
    std::pair<int, Partition> constructiveHeuristic(const Graph& graph);
}

/**
* idea : get every vertex
*/
namespace ConstructiveHeuristic_V3 {
    std::pair<int, Partition> constructiveHeuristic(const Graph& graph);

    int calculateMisclassifiedEdges(const Graph& graph, const std::unordered_set<int>& partition);
};

/**
 * Update from the first
 * idea : take the first algorithm but every time we check the vertex with the highest degree
 * result : not a big improvement but take * 5 more time
 */
namespace ConstructiveHeuristic_V4 {
    std::pair<int, Partition> constructiveHeuristic(const Graph& graph);
}

namespace ConstructiveHeuristic_Utils {
    int countEdges(int vertex, const std::vector<int> &vertexVector, const Graph& graph);
}

/**
 * the good constructive heuristic is the first
 */
namespace ConstructiveHeuristic = ConstructiveHeuristic_V1;