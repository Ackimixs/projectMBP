#include "ConstructiveHeuristic.hpp"

std::pair<int, Partition> ConstructiveHeuristic_V1::constructiveHeuristic(const Graph &graph) {
    const int numVertices = graph.size();

    if (numVertices % 2 != 0) {
        Logger::error("Number of vertices is not even", __CONTEXT__);
        exit(EXIT_FAILURE);
    }

    Partition part = std::make_pair(std::vector<int>(), std::vector<int>());

    part.first.push_back(0);
    int initialCutSize = 0;

    for (int i = 1; i < numVertices; ++i) {
        const int edgesToA = ConstructiveHeuristic_Utils:: countEdges(i, part.first, graph);
        const int edgesToB = ConstructiveHeuristic_Utils::countEdges(i, part.second, graph);

        if (edgesToA > edgesToB || (edgesToA == edgesToB && part.first.size() < part.second.size())) {
            part.first.push_back(i);
            initialCutSize += edgesToB;
        } else {
            part.second.push_back(i);
            initialCutSize += edgesToA;
        }
    }

    // Ensure both partitions have the same size
    while (part.first.size() != part.second.size()) {
        if (part.first.size() < part.second.size()) {
            int element = *part.second.begin();
            part.second.erase(part.second.begin());
            part.first.push_back(element);
        } else {
            int element = *part.first.begin();
            part.first.erase(part.first.begin());
            part.second.push_back(element);
        }
    }

    int cutSize = calculateCutSize(part, graph);

    return make_pair(cutSize, part);
}

std::pair<int, Partition> ConstructiveHeuristic_V3::constructiveHeuristic(const Graph &graph) {
    // Step 1: Initialization
    std::vector<int> partition1, partition2;

    // Alternate assignment to partitions while maintaining equal sizes
    partition1.push_back(0);

    // Step 2: Iterative Improvement
    for (int vertex = 1; vertex < graph.size(); ++vertex) {
        // Calculate misclassified edges for both partitions
        std::vector<int> newPartition1 = partition1;
        newPartition1.push_back(vertex);
        const int misclassified1 = calculateCutSize(std::make_pair(newPartition1, partition2), graph);

        std::vector<int> newPartition2 = partition2;
        newPartition2.push_back(vertex);
        const int misclassified2 = calculateCutSize(std::make_pair(newPartition2, partition1), graph);

        // Assign vertex to the partition with fewer misclassified edges
        if (misclassified1 < misclassified2) {
            partition1.push_back(vertex);
            partition2.erase(std::find(partition2.begin(), partition2.end(), vertex));
        } else {
            partition2.push_back(vertex);
            partition1.erase(std::find(partition1.begin(), partition1.end(), vertex));
        }
    }

    Logger::debug("Size of first partition : " + std::to_string(partition1.size()), __CONTEXT__);
    Logger::debug("Size of second partition : " + std::to_string(partition2.size()), __CONTEXT__);

    // Ensure both partitions have the same size
    while (partition1.size() != partition2.size()) {
        int vertex = partition1.size() > partition2.size() ? *partition1.begin() : *partition2.begin();
        const int misclassified1 = calculateCutSize(std::make_pair(partition1, partition2), graph);
        const int misclassified2 = calculateCutSize(std::make_pair(partition2, partition1), graph);

        if (misclassified1 < misclassified2) {
            partition1.erase(std::find(partition1.begin(), partition1.end(), vertex));
            partition2.push_back(vertex);
        } else {
            partition2.erase(std::find(partition2.begin(), partition2.end(), vertex));
            partition1.push_back(vertex);
        }
    }

    // Optional Step 4: Local Search

    int cutSize = calculateCutSize(std::make_pair(partition1, partition2), graph);

    // Step 5: Termination
    return std::make_pair(cutSize, std::make_pair(partition1, partition2));
}

int
ConstructiveHeuristic_V3::calculateMisclassifiedEdges(const Graph &graph, const std::unordered_set<int> &partition) {
    int misclassifiedEdges = 0;

    for (int u = 0; u < graph.size(); ++u) {
        for (int v : graph[u]) {
            // Check if the edge (u, v) is misclassified
            if (partition.count(u) == partition.count(v)) {
                misclassifiedEdges++;
            }
        }
    }

    // Each edge is counted twice, so divide by 2
    return misclassifiedEdges / 2;
}


std::pair<int, Partition> ConstructiveHeuristic_V4::constructiveHeuristic(const Graph &graph) {
    const int numVertices = graph.size();

    if (numVertices % 2 != 0) {
        Logger::error("Number of vertices is not even", __CONTEXT__);
        return std::make_pair(-1, std::make_pair(std::vector<int>(), std::vector<int>()));
    }

    Partition part;

    part.first.push_back(0);

    std::vector<int> reamingVertices;

    for (int i = 1; i < numVertices; ++i) {
        reamingVertices.push_back(i);
    }

    while (!reamingVertices.empty()) {
        int vertex = reamingVertices.back();
        for (int i = 0; i < reamingVertices.size(); ++i) {
            if (graph[reamingVertices[i]].size() > graph[vertex].size()) {
                vertex = reamingVertices[i];
            }
        }
        reamingVertices.erase(std::find(reamingVertices.begin(), reamingVertices.end(), vertex));

        const int edgesToA = ConstructiveHeuristic_Utils::countEdges(vertex, part.first, graph);
        const int edgesToB = ConstructiveHeuristic_Utils::countEdges(vertex, part.second, graph);

        if (edgesToA > edgesToB || (edgesToA == edgesToB && part.first.size() < part.second.size())) {
            part.first.push_back(vertex);
        } else {
            part.second.push_back(vertex);
        }
    }

    Logger::debug("Size of first partition : " + std::to_string(part.first.size()), __CONTEXT__);
    Logger::debug("Size of second partition : " + std::to_string(part.second.size()), __CONTEXT__);

    // Ensure both partitions have the same size
    // TODO Crash here in the else with first test graph
    while (part.first.size() != part.second.size()) {
        if (part.first.size() < part.second.size()) {
            int element = *part.second.end();
            part.second.erase(part.second.end());
            part.first.push_back(element);
        } else {
            int element = *part.first.end();
            part.first.erase(part.first.end());
            part.second.push_back(element);
        }
    }

    int cutSize = calculateCutSize(part, graph);

    return make_pair(cutSize, part);
}

int ConstructiveHeuristic_Utils::countEdges(const int vertex, const std::vector<int> &vertexVector, const Graph &graph) {
    int count = 0;
    for (int neighbor : graph[vertex]) {
        if (std::find(vertexVector.begin(), vertexVector.end(), neighbor) != vertexVector.end()) {
            count++;
        }
    }
    return count;
}

std::pair<int, Partition> ConstructiveHeuristic_V5::constructiveHeuristic(const Graph &graph) {
    if (graph.size() % 2 != 0) {
        Logger::error("Number of vertices is not even", __CONTEXT__);
        return std::make_pair(-1, std::make_pair(std::vector<int>(), std::vector<int>()));
    }

    Partition resPart;

    auto color = std::vector(graph.size(), BLUE);

    for (int v = 0; v < graph.size(); v++) {
        if (color[v] == BLUE) {
            dfs(v, graph, color, resPart);
        }
    }

    int cutSize = calculateCutSize(resPart, graph);

    return std::make_pair(cutSize, resPart);
}

void
ConstructiveHeuristic_V5::dfs(const int vertex, const Graph &graph, std::vector<Color> &color, Partition &res) {
    color[vertex] = WHITE;
    for (const int neighbor : graph[vertex]) {
        if (color[neighbor] == BLUE) {
            dfs(neighbor, graph, color, res);
        }
    }
    color[vertex] = RED;
    if (res.second.size() < graph.size() / 2) {
        res.second.push_back(vertex);
    } else {
        res.first.push_back(vertex);
    }
}

std::pair<int, Partition> ConstructiveHeuristic_V6::constructiveHeuristic(const Graph& graph) { // Complexity : O(n + m * (n log n)) => O(m * n log n)
    if (graph.size() % 2 != 0) {
        Logger::error("Number of vertices is not even", __CONTEXT__);
        return std::make_pair(-1, std::make_pair(std::vector<int>(), std::vector<int>()));
    }

    Partition resPart;

    auto color = std::vector(graph.size(), NONE);

    std::vector<std::pair<int, int>> vDeg = std::vector<std::pair<int, int>>(graph.size());

    for (int i = 0; i < graph.size(); i++) {
        vDeg[i] = std::make_pair(i, graph.degree(i));
    }

    std::sort(vDeg.begin(), vDeg.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.second > b.second;
    });// O(n log n)

    Color addTo = BLUE;

    for (auto [v, deg] : vDeg) {// O(n)
        if (color[v] == NONE) {
            color[v] = addTo;
            if (addTo == BLUE && resPart.first.size() < graph.size() / 2) {
                resPart.first.push_back(v);
            } else {
                resPart.second.push_back(v);
            }

            std::vector<std::pair<int, int>> neighborDegrees;
            for (auto neighbor : graph[v]) {
                if (color[neighbor] == NONE) {
                    neighborDegrees.emplace_back(neighbor, graph.degree(neighbor));
                }
            }
            std::sort(neighborDegrees.begin(), neighborDegrees.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                return a.second < b.second;
            });// O(n log n)

            for (int k = 0; k < neighborDegrees.size() / 2; k++) {// O(n)
                auto [neighbor, _x] = neighborDegrees[k];
                if (color[neighbor] == NONE) {
                    color[neighbor] = addTo;
                    if (addTo == BLUE && resPart.first.size() < graph.size() / 2) {
                        resPart.first.push_back(neighbor);
                    } else {
                        resPart.second.push_back(neighbor);
                    }
                }
            }

            addTo = addTo == BLUE ? RED : BLUE;
        }
    }

    return std::make_pair(calculateCutSize(resPart, graph), resPart);
}

std::pair<int, Partition> ConstructiveHeuristic_V7::constructiveHeuristic(const Graph& graph) {
    if (graph.size() % 2 != 0) {
        Logger::error("Number of vertices is not even", __CONTEXT__);
        return std::make_pair(-1, std::make_pair(std::vector<int>(), std::vector<int>()));
    }

    Partition resPart;

    auto color = std::vector(graph.size(), NONE);

    // Use a priority queue instead of a vector
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::less<>> vDeg;

    for (int i = 0; i < graph.size(); i++) {
        vDeg.push(std::make_pair(graph.degree(i), i));
    }

    Color addTo = BLUE;

    while (!vDeg.empty()) {
        auto [deg, v] = vDeg.top();
        vDeg.pop();

        if (color[v] == NONE) {
            color[v] = addTo;
            if (addTo == BLUE && resPart.first.size() < graph.size() / 2) {
                resPart.first.push_back(v);
            } else {
                resPart.second.push_back(v);
            }

            std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::less<>> neighborDegrees;
            for (auto neighbor : graph[v]) {
                if (color[neighbor] == NONE) {
                    neighborDegrees.push(std::make_pair(graph.degree(neighbor), neighbor));
                }
            }

            while (!neighborDegrees.empty()) {
                auto [neighborDeg, maxNeighbor] = neighborDegrees.top();
                neighborDegrees.pop();
                if (color[maxNeighbor] == NONE) {
                    color[maxNeighbor] = addTo;
                    if (addTo == BLUE && resPart.first.size() < graph.size() / 2) {
                        resPart.first.push_back(maxNeighbor);
                    } else {
                        resPart.second.push_back(maxNeighbor);
                    }
                }
            }

            addTo = addTo == BLUE ? RED : BLUE;
        }
    }

    return std::make_pair(calculateCutSize(resPart, graph), resPart);
}