#include "ExactAlgorithm.hpp"

std::pair<int, Partition> exact_V1::exactAlgorithm(const Graph& g) {

    int minNumberOfVertex = INT_MAX;

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

        if (numberOfVertex < minNumberOfVertex) {
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

std::pair<int, Partition> exact_V2::exactAlgorithm(const Graph &g) {
    std::unordered_set<int> set;
    set.insert(0);
    Partition part;
    int partSize = INT_MAX;

    exact_V2::checkAllPair(g, part, partSize, set, g.size(), 1);

    return std::make_pair(partSize, part);
}

void exact_V2::checkAllPair(const Graph &g, Partition &part, int &partSize, std::unordered_set<int> set, int n, int start, int k) {

    if (set.size() == g.size() / 2) {

        std::unordered_set<int> oppositeSet;

        for (int i = 0; i < g.size(); i++) {
            if (!set.contains(i)) {
                oppositeSet.insert(i);
            }
        }

        int numberOfVertex = 0;
        for (int m : set) {
            for (int l : oppositeSet) {
                if (g.isEdge(m, l)) {
                    numberOfVertex++;
                }
            }
        }

        if (numberOfVertex < partSize) {
            part = std::make_pair(set, oppositeSet);

            partSize = calculateCutSize(part, g);
        }

        return;
    }

    else {
        for (int i = start; i < n / 2 + k; i++) {
            std::unordered_set<int> newSet = set;

            newSet.insert(i);

            if (!checkPartition(g, partSize, newSet)) {
                continue;
            }

            checkAllPair(g, part, partSize, newSet, n, i + 1, k + 1);
        }
    }
}

bool exact_V2::checkPartition(const Graph &g, int &partSize, std::unordered_set<int> set) {

    std::unordered_set<int> oppositeSet;

    // the oppositeSet is all the vertex before the greatest of the set
    for (int i = 0; i < (*set.begin()); i++) {
        if (!set.contains(i)) {
            oppositeSet.insert(i);
        }
    }

    int numberOfVertex = 0;
    for (int k : set) {
        for (int l : oppositeSet) {
            if (g.isEdge(k, l)) {
                numberOfVertex++;
            }
        }
    }

    return numberOfVertex < partSize;
}

int exact_V2::calculateCutSize(const Partition &partition, const Graph &graph) {
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