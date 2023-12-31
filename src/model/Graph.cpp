#include "Graph.hpp"

Graph::Graph() : _size(0), _m(0) {
    Logger::debug("Creating default graph...", __CONTEXT__);
}

Graph::Graph(const unsigned long size) : _adjList(size), _successor(size), _predecessor(size), _adjMatrix(size * size, false), _size(size), _m(0) {
    Logger::debug("Creating a undirected graph of size " + std::to_string(size), __CONTEXT__);
}

Graph::Graph(const Graph &graph) : _adjList(graph._adjList), _successor(graph._successor), _predecessor(graph._predecessor), _adjMatrix(graph._adjMatrix),
                                   _size(graph._size), _m(graph._m) {
    Logger::debug("Creating a copy of a graph...", __CONTEXT__);
}

Graph::~Graph() {
    Logger::debug("Destroying graph...", __CONTEXT__);
}

unsigned int Graph::size() const {
    return _size;
}

unsigned int Graph::m() const {
    return _m;
}

std::vector<int> Graph::operator[](const int vertex) const {
    return this->_adjList[vertex];
}

std::vector<int> Graph::successor(const int vertex) const {
    return this->_successor[vertex];
}

std::vector<int> Graph::predecessor(const int vertex) const {
    return this->_predecessor[vertex];
}

void Graph::addEdge(const int from, const int to) {
    if (from < 0 || from > this->size() - 1) {
        throw std::invalid_argument("'from' need to be between 0 and the _size of the graph - 1");
    } else if (to < 0 || to > this->size() - 1) {
        throw std::invalid_argument("'to' need to be between 0 and the _size of the graph - 1");
    }

    this->_m++;
    this->_adjList[from].push_back(to);
    this->_adjList[to].push_back(from);
    this->_successor[from].push_back(to);
    this->_predecessor[to].push_back(from);
    this->_adjMatrix[from * _size + to] = true;
    this->_adjMatrix[to * _size + from] = true;
}

bool Graph::removeEdge(const int from, const int to) {
    Logger::debug("Removing edge " + std::to_string(from) + " -> " + std::to_string(to), __CONTEXT__);
    if (from < 0 || from > this->size() - 1) {
        throw std::invalid_argument("'from' need to be between 0 and the _size of the graph - 1");
    } else if (to < 0 || to > this->size() - 1) {
        throw std::invalid_argument("'to' need to be between 0 and the _size of the graph - 1");
    }

    bool res = false;
    for (int i = 0; i < this->_adjList[from].size(); i++) {
        if (this->_adjList[from][i] == to) {
            this->_adjList[from].erase(this->_adjList[from].begin() + i);
            res = true;
        }
    }

    if (!res) {
        Logger::debug("Edge " + std::to_string(from) + " -> " + std::to_string(to) + " not found", __CONTEXT__);
        return false;
    }

    res = false;

    for (int i = 0; i < this->_adjList[to].size(); i++) {
        if (this->_adjList[to][i] == from) {
            this->_adjList[to].erase(this->_adjList[to].begin() + i);
            res = true;
        }
    }

    if (!res) {
        Logger::debug("Edge " + std::to_string(to) + " -> " + std::to_string(from) + " not found", __CONTEXT__);
        return false;
    }

    res = false;

    for (int i = 0; i < this->_successor[from].size(); i++) {
        if (this->_successor[from][i] == to) {
            this->_successor[from].erase(this->_successor[from].begin() + i);
            res = true;
        }
    }

    for (int i = 0; i < this->_predecessor[to].size(); i++) {
        if (this->_predecessor[to][i] == from) {
            this->_predecessor[to].erase(this->_predecessor[to].begin() + i);
            res = true;
        }
    }

    if (!res) {
        Logger::debug("Edge " + std::to_string(from) + " -> " + std::to_string(to) + " not found", __CONTEXT__);
        return false;
    }

    this->_adjMatrix[from * size() + to] = false;
    this->_adjMatrix[to * size() + from] = false;

    return res;
}

bool Graph::isEdge(const int from, const int to) const {
    return this->_adjMatrix[from * size() + to];
}

int Graph::degree(const int vertex) const {
    return static_cast<int>(this->_adjList[vertex].size());
}

std::vector<int> Graph::BFS(const int start) const {
    Logger::debug("BFS algorithm starting...", __CONTEXT__);

    auto color = std::vector(this->size(), BLUE);
    auto parent = std::vector(this->size(), -1);
    std::vector<int> res;

    this->BFSVisit(start, color, parent, res);
    for (int v = 0; v < this->size(); v++) {
        if (color[v] == BLUE) {
            this->BFSVisit(v, color, parent, res);
        }
    }

    return res;
}

void Graph::BFSVisit(const int vertex, std::vector<Color> &color, std::vector<int> &parent, std::vector<int> &res) const {
    std::queue<int> q;
    color[vertex] = WHITE;
    q.push(vertex);
    while (!q.empty()) {
        int w = q.front();
        q.pop();
        for (int z : this->_adjList[w]) {
            if (color[z] == BLUE) {
                color[z] = WHITE;
                parent[z] = w;
                q.push(z);
            }
        }
        color[w] = RED;
        res.push_back(w);
    }
}

std::vector<int> Graph::DFS(const int start, const typeOfOutput type) {
    Logger::debug("DFS algorithm starting...", __CONTEXT__);

    auto color = std::vector(this->size(), BLUE);
    auto parent = std::vector(this->size(), -1);
    std::vector<int> res;

    this->DFSVisit(start, color, parent, res, type);
    for (int v = 0; v < this->size(); v++) {
        if (color[v] == BLUE) {
            this->DFSVisit(v, color, parent, res, type);
        }
    }
    return res;
}

void Graph::DFSVisit(const int vertex, std::vector<Color> &color, std::vector<int> &parent, std::vector<int> &res,
                     const typeOfOutput type) {
    color[vertex] = WHITE;
    if (type == PREORDER) {
        res.push_back(vertex);
    }
    for (const int w : this->_adjList[vertex]) {
        if (color[w] == BLUE) {
            parent[w] = vertex;
            this->DFSVisit(w, color, parent, res, type);
        }
    }
    color[vertex] = RED;
    if (type == POSTORDER) {
        res.push_back(vertex);
    }
}

Graph Graph::createRandomGraph(const int numberOfVertices, const double edgeProbability) {
    Logger::debug("Creating random graph with " + std::to_string(numberOfVertices) + " vertices and edge probability " + std::to_string(edgeProbability) + "...", __CONTEXT__);

    if (numberOfVertices <= 0 || edgeProbability < 0.0 || edgeProbability > 1.0) {
        throw std::invalid_argument("Invalid input parameters.");
    }

    // Initialize random number generator
    std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));
    std::uniform_real_distribution distribution(0.0, 1.0);

    auto g = Graph(numberOfVertices);
    for (int i = 0; i < numberOfVertices; i++) {
        for (int j = i + 1; j < numberOfVertices; j++) {
            if (distribution(rng) < edgeProbability) {
                g.addEdge(i, j);
            }
        }
    }

    Logger::info("Random graph created with " + LogColor::fgBrightRed + std::to_string(g.size()) + LogColor::reset + " vertex and " + LogColor::fgBrightRed + std::to_string(g.m()) + LogColor::reset + " edge.", __CONTEXT__);

    return g;
}

void Graph::print() const {
    Logger::debug("Printing graph...", __CONTEXT__);

    for (int i = 0; i < this->size(); i++) {
        std::cout << i << " -> ";
        for (const int j : this->_adjList[i]) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
}

bool Graph::isBipartite() {
    Logger::debug("Bipartite algorithm starting...", __CONTEXT__);
    auto color = std::vector(this->size(), BLUE);
    auto partie = std::vector(this->size(), NONE);
    auto parent = std::vector(this->size(), -1);

    for (int v = 0; v < this->size(); v++) {
        if (color[v] == BLUE) {
            partie[v] = BLUE;
            const bool res = this->isBipartiteVisit(v, color, parent, partie);
            if (!res) {
                return false;
            }
        }
    }
    return true;
}

bool
Graph::isBipartiteVisit(const int vertex, std::vector<Color> &color, std::vector<int> &parent, std::vector<Color> &part) const {
    std::queue<int> q;
    color[vertex] = WHITE;
    q.push(vertex);
    while (!q.empty()) {
        const int w = q.front();
        q.pop();
        const Color nextColor = part[w] == BLUE ? RED : BLUE;
        for (int z : this->_adjList[w]) {

            // PART TO CHECK IF THE GRAPH IS BIPARTITE
            if (part[z] != NONE) {
                if (part[z] == part[w]) {
                    return false;
                }
            } else {
                part[z] = nextColor;
            }

            if (color[z] == BLUE) {
                color[z] = WHITE;
                parent[z] = w;
                q.push(z);
            }
        }
        color[w] = RED;
    }
    return true;
}

int calculateCutSize(const Partition &partition, const Graph &graph) {
    int cutSize = 0;

    for (const int i : partition.first) {
        for (const int j : partition.second) {
            if (graph.isEdge(i, j)) {
                cutSize++;
            }
        }
    }

    return cutSize;
}
