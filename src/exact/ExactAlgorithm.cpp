#include "ExactAlgorithm.hpp"

std::pair<int, Partition> Exact_V1::exactAlgorithm(const Graph& g) {

    if (g.size() % 2 != 0) {
        Logger::error("Number of vertices is not even", __CONTEXT__);
        exit(EXIT_FAILURE);
    }

    int minNumberOfVertex = __INT_MAX__;

    std::pair<std::vector<int>, std::vector<int>> res;

    // get every pair like [[0, 1, 2], [0, 1, 3], [0, 1, 4], ...]
    auto pair = getAllPair(g.size());

    for (int j = 0; j < pair.size(); j++) {
        // Convert vector to unordered_set
        std::vector<int> vec1 = pair[j];
        std::vector<int> vec2 = pair[pair.size() - 1 - j];

        int numberOfVertex = 0;

        for (const int k : vec1) {
            for (const int l : vec2) {
                if (g.isEdge(k, l)) {
                    numberOfVertex++;
                }
            }
        }

        if (numberOfVertex < minNumberOfVertex) {
            minNumberOfVertex = numberOfVertex;
            res = std::make_pair(vec1, vec2);
        }

    }

    return std::make_pair(minNumberOfVertex, res);
}

void Exact_V1::generateCombinations(std::vector<int>& currentCombination, int start, int n, int k, std::vector<std::vector<int>>& result) {
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

std::vector<std::vector<int>> Exact_V1::getAllPair(int n) {

    std::vector<std::vector<int>> result;

    // Ensure n is even
    if (n % 2 != 0) {
        Logger::error("The number of vertex must be even", __CONTEXT__);
        return result;
    }

    const int k = n / 2;

    std::vector<int> currentCombination;

    generateCombinations(currentCombination, 0, n, k, result);

    return result;
}

std::pair<int, Partition> Exact_V2::exactAlgorithm(const Graph &g) { // O(2^n)
    if (g.size() % 2 != 0) {
        Logger::error("Number of vertices is not even", __CONTEXT__);
        return std::make_pair(-1, std::make_pair(std::vector<int>(), std::vector<int>()));
    }

    std::vector<int> vec;
    vec.push_back(0);
    Partition part;
    int partSize = __INT_MAX__;

    checkAllPair(g, part, partSize, vec, g.size(), 1);

    return std::make_pair(partSize, part);
}

void Exact_V2::checkAllPair(const Graph &g, Partition &part, int &partSize, std::vector<int> vector, const int n, const int start, const int k) {

    if (vector.size() == (g.size() / 2)) {

        std::vector<int> oppositeSet;

        for (int i = 0; i < g.size(); i++) {
            if (std::find(vector.begin(), vector.end(), i) != vector.end()) {
                oppositeSet.push_back(i);
            }
        }

        int numberOfVertex = 0;
        for (const int m : vector) {
            for (const int l : oppositeSet) {
                if (g.isEdge(m, l)) {
                    numberOfVertex++;
                }
            }
        }

        if (numberOfVertex < partSize) {
            part = std::make_pair(vector, oppositeSet);

            partSize = calculateCutSize(part, g);
        }
    }

    else {
        for (int i = start; i < n / 2 + k; i++) {
            std::vector<int> newSet = vector;

            newSet.push_back(i);

            if (!checkPartition(g, partSize, newSet)) { // O(n^2)
                continue;
            }

            checkAllPair(g, part, partSize, newSet, n, i + 1, k + 1);
        }
    }
}

bool Exact_V2::checkPartition(const Graph &g, const int &partSize, std::vector<int> vec) { // O(n^2)

    std::vector<int> oppositeSet;

    // the oppositeSet is all the vertex before the greatest of the set
    for (int i = 0; i < (*vec.begin()); i++) {
        if (std::find(vec.begin(), vec.end(), i) == vec.end()) {
            oppositeSet.push_back(i);
        }
    }

    int numberOfVertex = 0;
    for (const int k : vec) {
        for (const int l : oppositeSet) {
            if (g.isEdge(k, l)) {
                numberOfVertex++;
            }
        }
    }

    return numberOfVertex < partSize;
}
