#include "ConstructiveHeuristic.hpp"

std::pair<int, Partition> ConstructiveHeuristic_V1::constructiveHeuristic(const Graph &graph) {
    int numVertices = graph.size();

    if (numVertices % 2 != 0) {
        Logger::error("Number of vertices is not even", __CONTEXT__);
        exit(EXIT_FAILURE);
    }

    Partition part = std::make_pair(std::unordered_set<int>(), std::unordered_set<int>());

    part.first.insert(0);
    int initialCutSize = 0;

    for (int i = 1; i < numVertices; ++i) {
        int edgesToA = countEdges(i, part.first, graph);
        int edgesToB = countEdges(i, part.second, graph);

        if (edgesToA > edgesToB || (edgesToA == edgesToB && part.first.size() < part.second.size())) {
            part.first.insert(i);
            initialCutSize += edgesToB;
        } else {
            part.second.insert(i);
            initialCutSize += edgesToA;
        }
    }

    Logger::debug("Size of first partition : " + std::to_string(part.first.size()), __CONTEXT__);
    Logger::debug("Size of second partition : " + std::to_string(part.second.size()), __CONTEXT__);

    // Ensure both partitions have the same size
    // TODO the only part of the graph that is not optimized i think
    while (part.first.size() != part.second.size()) {
        if (part.first.size() < part.second.size()) {
            int element = *part.second.begin();
            part.second.erase(element);
            part.first.insert(element);
        } else {
            int element = *part.first.begin();
            part.first.erase(element);
            part.second.insert(element);
        }
    }

    int cutSize = calculateCutSize(part, graph);

    return make_pair(cutSize, part);
}

int ConstructiveHeuristic_V1::countEdges(int vertex, const std::unordered_set<int> &vertexSet, const Graph &graph) {
    int count = 0;
    for (int neighbor : graph[vertex]) {
        if (vertexSet.count(neighbor) > 0) {
            count++;
        }
    }
    return count;
}

std::pair<int, Partition> ConstructiveHeuristic_V3::constructiveHeuristic(const Graph &graph) {
    // Step 1: Initialization
    std::unordered_set<int> partition1, partition2;

    // Alternate assignment to partitions while maintaining equal sizes
    partition1.insert(0);

    // Step 2: Iterative Improvement
    for (int vertex = 1; vertex < graph.size(); ++vertex) {
        // Calculate misclassified edges for both partitions
        std::unordered_set<int> newPartition1 = partition1;
        newPartition1.insert(vertex);
        int misclassified1 = calculateCutSize(std::make_pair(newPartition1, partition2), graph);

        std::unordered_set<int> newPartition2 = partition2;
        newPartition2.insert(vertex);
        int misclassified2 = calculateCutSize(std::make_pair(newPartition2, partition1), graph);

        // Assign vertex to the partition with fewer misclassified edges
        if (misclassified1 < misclassified2) {
            partition1.insert(vertex);
            partition2.erase(vertex);
        } else {
            partition2.insert(vertex);
            partition1.erase(vertex);
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
            partition1.erase(vertex);
            partition2.insert(vertex);
        } else {
            partition2.erase(vertex);
            partition1.insert(vertex);
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
        return std::make_pair(-1, std::make_pair(std::unordered_set<int>(), std::unordered_set<int>()));
    }

    Partition part;

    part.first.insert(0);

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

        int edgesToA = countEdges(vertex, part.first, graph);
        int edgesToB = countEdges(vertex, part.second, graph);

        if (edgesToA > edgesToB || (edgesToA == edgesToB && part.first.size() < part.second.size())) {
            part.first.insert(vertex);
        } else {
            part.second.insert(vertex);
        }
    }

    Logger::debug("Size of first partition : " + std::to_string(part.first.size()), __CONTEXT__);
    Logger::debug("Size of second partition : " + std::to_string(part.second.size()), __CONTEXT__);

    // Ensure both partitions have the same size
    // TODO Crash here in the else with first test graph
    while (part.first.size() != part.second.size()) {
        if (part.first.size() < part.second.size()) {
            int element = *part.second.end();
            part.second.erase(element);
            part.first.insert(element);
        } else {
            int element = *part.first.end();
            part.first.erase(element);
            part.second.insert(element);
        }
    }

    int cutSize = calculateCutSize(part, graph);

    return make_pair(cutSize, part);
}

int ConstructiveHeuristic_V4::countEdges(int vertex, const std::unordered_set<int> &vertexSet, const Graph &graph) {
    int count = 0;
    for (int neighbor : graph[vertex]) {
        if (vertexSet.count(neighbor) > 0) {
            count++;
        }
    }
    return count;
}
