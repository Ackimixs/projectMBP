#pragma once

#include "Logger.hpp"

#include <vector>
#include <algorithm>
#include <queue>
#include <random>
#include <unordered_set>

enum Color {
    NONE,
    BLUE,
    WHITE,
    RED
};

enum typeOfOutput {
    PREORDER,
    POSTORDER
};

typedef std::pair<std::unordered_set<int>, std::unordered_set<int>> Partition;

class Graph {
private:
    std::vector<std::vector<int>> _adjList;
    std::vector<std::vector<int>> _successor;
    std::vector<std::vector<int>> _predecessor;

    std::vector<std::vector<int>> _adjMatrix;

    int _size;
    int _m;

protected:
    void BFSVisit(int vertex, std::vector<Color> &color, std::vector<int> &parent, std::vector<int> &res);

    void DFSVisit(int vertex, std::vector<Color> &color, std::vector<int> &parent, std::vector<int> &res, typeOfOutput type);

    bool isBipartiteVisit(int vertex, std::vector<Color> &color, std::vector<int> &parent, std::vector<Color> &part);

public:
    Graph();

    Graph(int size);

    Graph(const Graph& graph);

    ~Graph();

    static Graph createRandomGraph(int numberOfVertices, double edgeProbability = 0.5);

    [[nodiscard]] int size() const;

    [[nodiscard]] int m() const;

    // access to adjList
    std::vector<int> operator[](int vertex) const;

    // access to the successor list
    [[nodiscard]] std::vector<int> successor(int vertex) const;

    // access to the predecessor list
    [[nodiscard]] std::vector<int> predecessor(int vertex) const;

    void addEdge(int from, int to);

    bool removeEdge(int from, int to);

    [[nodiscard]] bool isEdge(int from, int to) const;

    int degree(int vertex);

    std::vector<int> BFS(int start = 0);

    std::vector<int> DFS(int start = 0, typeOfOutput type = typeOfOutput::PREORDER);

    bool isBipartite();

    void print();
};

int calculateCutSize(const Partition &partition, const Graph &graph);
int calculateCutSize(const std::pair<std::vector<int>, std::vector<int>> &partition, const Graph &graph);