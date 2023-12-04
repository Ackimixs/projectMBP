#pragma once

#include "Logger.hpp"

#include <vector>
#include <algorithm>
#include <queue>
#include <random>
#include <unordered_set>
#include <map>

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

typedef std::pair<std::vector<int>, std::vector<int>> Partition;

// When the size of the graph is big (n = 100000) the program crash due to the adjMatrix size
class Graph {
private:
    // maybe better as: std::map<int, std::unordered_set<int>> (but for the moment I don't want to change it)
    // I will test it in local and see if it's better
    std::vector<std::vector<int>> _adjList;
    std::vector<std::vector<int>> _successor;
    std::vector<std::vector<int>> _predecessor;

//    std::vector<std::vector<int>> _adjMatrix;
    std::vector<bool> _adjMatrix;

    unsigned int _size;
    unsigned int _m;

protected:
    void BFSVisit(int vertex, std::vector<Color> &color, std::vector<int> &parent, std::vector<int> &res) const;

    void DFSVisit(int vertex, std::vector<Color> &color, std::vector<int> &parent, std::vector<int> &res, typeOfOutput type);

    bool isBipartiteVisit(int vertex, std::vector<Color> &color, std::vector<int> &parent, std::vector<Color> &part) const;

public:
    Graph();

    Graph(unsigned long size);

    Graph(const Graph& graph);

    ~Graph();

    static Graph createRandomGraph(int numberOfVertices, double edgeProbability = 0.5);

    [[nodiscard]] unsigned int size() const;

    [[nodiscard]] unsigned m() const;

    // access to adjList
    std::vector<int> operator[](int vertex) const;

    // access to the successor list
    [[nodiscard]] std::vector<int> successor(int vertex) const;

    // access to the predecessor list
    [[nodiscard]] std::vector<int> predecessor(int vertex) const;

    void addEdge(int from, int to);

    bool removeEdge(int from, int to);

    [[nodiscard]] bool isEdge(int from, int to) const;

    int degree(int vertex) const;

    std::vector<int> BFS(int start = 0) const;

    std::vector<int> DFS(int start = 0, typeOfOutput type = PREORDER);

    bool isBipartite();

    void print() const;
};

int calculateCutSize(const Partition &partition, const Graph &graph);