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
    std::vector<std::vector<int>> adjList;
    std::vector<std::vector<int>> adjListDirected;
    int _size;
    int _m;

protected:
    void BFSVisit(int vertex, std::vector<Color> &color, std::vector<int> &parent, std::vector<int> &res);

    void DFSVisit(int vertex, std::vector<Color> &color, std::vector<int> &parent, std::vector<int> &res, typeOfOutput type);

    bool isBipartiteVisit(int vertex, std::vector<Color> &color, std::vector<int> &parent, std::vector<Color> &partie);

public:
    Graph();

    Graph(int size);

    Graph(const Graph& graph);

    ~Graph();

    static Graph createRandomGraph(int numberOfVertices, double edgeProbability = 0.5);

    [[nodiscard]] int size() const;

    int m() const;

    std::vector<int> operator[](int vertex) const;

    std::vector<int> directed(int vertex) const;

    void addEdge(int from, int to);

    bool removeEdge(int from, int to);

    bool isEdge(int from, int to) const;

    int degres(int vertex);

    std::vector<int> BFS(int start = 0);

    std::vector<int> DFS(int start = 0, typeOfOutput type = typeOfOutput::PREORDER);

    bool isBipartite();

    void print();
};
