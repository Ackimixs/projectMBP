#include "ConstructiveHeuristic.hpp"

std::pair<int, Partition> ConstructiveHeuristic_V1::constructiveHeuristic(const Graph &graph) {
    int numVertices = graph.size();

    if (numVertices % 2 != 0) {
        Logger::error("Number of vertices is not even", __CONTEXT__);
        exit(EXIT_FAILURE);
    }

    Partition part = std::make_pair(std::vector<int>(), std::vector<int>());

    part.first.push_back(0);
    int initialCutSize = 0;

    for (int i = 1; i < numVertices; ++i) {
        int edgesToA = ConstructiveHeuristic_Utils:: countEdges(i, part.first, graph);
        int edgesToB = ConstructiveHeuristic_Utils::countEdges(i, part.second, graph);

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
        int misclassified1 = calculateCutSize(std::make_pair(newPartition1, partition2), graph);

        std::vector<int> newPartition2 = partition2;
        newPartition2.push_back(vertex);
        int misclassified2 = calculateCutSize(std::make_pair(newPartition2, partition1), graph);

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
        int misclassified1 = calculateCutSize(std::make_pair(partition1, partition2), graph);
        int misclassified2 = calculateCutSize(std::make_pair(partition2, partition1), graph);

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
    int numVertices = graph.size();

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

        int edgesToA = ConstructiveHeuristic_Utils::countEdges(vertex, part.first, graph);
        int edgesToB = ConstructiveHeuristic_Utils::countEdges(vertex, part.second, graph);

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

int ConstructiveHeuristic_Utils::countEdges(int vertex, const std::vector<int> &vertexVector, const Graph &graph) {
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

    std::vector<Color> color = std::vector<Color>(graph.size(), Color::BLUE);

    std::vector<int> res;

    for (int v = 0; v < graph.size(); v++) {
        if (color[v] == Color::BLUE) {
            dfs(v, graph, color, res);
        }
    }

    for (int i = 0; i < graph.size() / 2; i++) {
        resPart.first.push_back(res[i]);
    }
    for (int i = graph.size() / 2; i < graph.size(); i++) {
        resPart.second.push_back(res[i]);
    }

    int cutSize = calculateCutSize(resPart, graph);

    return std::make_pair(cutSize, resPart);
}

void
ConstructiveHeuristic_V5::dfs(int vertex, const Graph &graph, std::vector<Color> &color, std::vector<int> &res) {
    color[vertex] = Color::WHITE;
    for (int neighbor : graph[vertex]) {
        if (color[neighbor] == Color::BLUE) {
            dfs(neighbor, graph, color, res);
        }
    }
    color[vertex] = Color::RED;
    res.push_back(vertex);
}