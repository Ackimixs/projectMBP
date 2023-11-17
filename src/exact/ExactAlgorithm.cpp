#include "ExactAlgorithm.hpp"

std::pair<int, Partition> exact_V1::exactAlgorithm(const Graph& g) {

    int minNumberOfVertex = -1;

    std::pair<std::unordered_set<int>, std::unordered_set<int>> res;

    auto pair = getAllPair(g.size());

    for (int j = 0; j < pair.size() / 2; j++) {
        std::unordered_set<int> set1;
        std::unordered_set<int> set2;
        for (auto v : pair[j]) {
            set1.insert(v);
        }
        for (auto v : pair[pair.size() - (j + 1)]) {
            set2.insert(v);
        }


        int numberOfVertex = 0;

        for (int k : set1) {
            for (int l : set2) {
                if (g.isEdge(k, l)) {
                    numberOfVertex++;
                }
            }
        }

        if (numberOfVertex < minNumberOfVertex || minNumberOfVertex == -1) {
            minNumberOfVertex = numberOfVertex;
            res = std::make_pair(set1, set2);
        }

    }

    return std::make_pair(minNumberOfVertex, res);
}

void exact_V1::generateCombinations(std::vector<int>& currentCombination, int start, int n, int k, std::vector<std::vector<int>>& result) {
    if (k == 0) {
        // Add the current combination to the result vector
        result.push_back(currentCombination);
        return;
    }

    for (int i = start; i < n; ++i) {
        currentCombination.push_back(i);
        generateCombinations(currentCombination, i + 1, n, k - 1, result);
        currentCombination.pop_back();
    }
}

std::vector<std::vector<int>> exact_V1::getAllPair(int n) {

    std::vector<std::vector<int>> result;

    // Ensure n is even
    if (n % 2 != 0) {
        Logger::error("The number of vertex must be even", __CONTEXT__);
        return result;
    }

    int k = n / 2;

    std::vector<int> currentCombination;

    generateCombinations(currentCombination, 0, n, k, result);

    return result;
}


int exact_V2::calculateCutSize(const Partition &partition, const Graph& graph) {
    int cutSize = 0;

    for (int i : partition.first) {
        for (int j : partition.second) {
            if (graph.isEdge(i, j)) {
                cutSize++;
            }
        }
    }

    return cutSize;
}

void
exact_V2::explorePartitions(Partition &partition, int vertex, int &minCut, Partition &minPartition, const Graph &graph) {
    // Function to explore all possible partitions of the graph

    if (vertex == graph.size()) {
        if (partition.first.size() != partition.second.size()) {
            return;
        }

        int cutSize = calculateCutSize(partition, graph);

        if (cutSize < minCut) {
            minCut = cutSize;
            minPartition = partition;
        }

        return;
    }

    partition.first.insert(vertex);
    explorePartitions(partition, vertex + 1, minCut, minPartition, graph);

    partition.first.erase(vertex);
    partition.second.insert(vertex);
    explorePartitions(partition, vertex + 1, minCut, minPartition, graph);

    partition.second.erase(vertex);
}

std::pair<int, Partition> exact_V2::exactAlgorithm(const Graph &g) {
    Partition partition;  // Initial partition
    int minCut = INT_MAX;
    Partition minPartition;

    explorePartitions(partition, 0, minCut, minPartition, g);

    return make_pair(minCut, minPartition);
}