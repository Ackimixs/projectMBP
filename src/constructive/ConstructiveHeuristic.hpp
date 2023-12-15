#pragma once

#include "../model/Graph.hpp"

#include <unordered_set>

// TODO did a constructive heuristic with the degree of the vertex because dfs work but we do not know why

/**
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
 * idea : dfs
 * result : so fucking good but idk why
 */
namespace ConstructiveHeuristic_V5 {
    std::pair<int, Partition> constructiveHeuristic(const Graph& graph);

    void dfs(int vertex, const Graph &graph, std::vector<Color> &color, Partition &res);
}

/**
 * degrees
 * idea : create a vector with a vectex and it degrees, sort it in descending by degrees
*/
namespace ConstructiveHeuristic_V6 {
    std::pair<int, Partition> constructiveHeuristic(const Graph& graph);
}

/**
 * \brief degres with std::priority_queue
 * same as V6
 */
namespace ConstructiveHeuristic_V7 {
    std::pair<int, Partition> constructiveHeuristic(const Graph& graph);
}

/**
 * the good constructive heuristic
 */
namespace ConstructiveHeuristic = ConstructiveHeuristic_V6;
