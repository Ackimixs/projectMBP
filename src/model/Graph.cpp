#include "Graph.hpp"

Graph::Graph() : _size(0), adjList(), adjListDirected() {
    Logger::debug("Creating default graph...", __CONTEXT__);
}

Graph::Graph(int size) : _size(size) {
    Logger::debug("Creating a directed graph of size " + std::to_string(size), __CONTEXT__);

    this->adjList = std::vector<std::vector<int>>(size);
    this->adjListDirected = std::vector<std::vector<int>>(size);
}

Graph::Graph(const Graph &graph) : _size(graph._size) {
    Logger::debug("Creating a copy of a graph...", __CONTEXT__);

    this->adjList = graph.adjList;
    this->adjListDirected = graph.adjListDirected;
}

Graph::~Graph() {
    Logger::debug("Destroying graph...", __CONTEXT__);
}

int Graph::size() const {
    return _size;
}

int Graph::m() const {
    int res = 0;
    for (int i = 0; i < this->size(); i++) {
        res += int(this->adjList[i].size());
    }
    return res;
}

std::vector<int> Graph::operator[](int vertex) const {
    return this->adjList[vertex];
}

std::vector<int> Graph::directed(int vertex) const {
    return this->adjListDirected[vertex];
}

void Graph::addEdge(int from, int to) {
    if (from < 0 || from > this->size() - 1) {
        throw std::invalid_argument("'from' need to be between 0 and the _size of the graph - 1");
    } else if (to < 0 || to > this->size() - 1) {
        throw std::invalid_argument("'to' need to be between 0 and the _size of the graph - 1");
    }

    this->adjList[from].push_back(to);
    this->adjList[to].push_back(from);
    this->adjListDirected[from].push_back(to);
}

bool Graph::removeEdge(int from, int to) {
    Logger::debug("Removing edge " + std::to_string(from) + " -> " + std::to_string(to), __CONTEXT__);
    if (from < 0 || from > this->size() - 1) {
        throw std::invalid_argument("'from' need to be between 0 and the _size of the graph - 1");
    } else if (to < 0 || to > this->size() - 1) {
        throw std::invalid_argument("'to' need to be between 0 and the _size of the graph - 1");
    }

    bool res = false;
    for (int i = 0; i < this->adjList[from].size(); i++) {
        if (this->adjList[from][i] == to) {
            this->adjList[from].erase(this->adjList[from].begin() + i);
            res = true;
        }
    }

    if (!res) {
        Logger::debug("Edge " + std::to_string(from) + " -> " + std::to_string(to) + " not found", __CONTEXT__);
        return false;
    }

    res = false;

    for (int i = 0; i < this->adjList[to].size(); i++) {
        if (this->adjList[to][i] == from) {
            this->adjList[to].erase(this->adjList[to].begin() + i);
            res = true;
        }
    }

    if (!res) {
        Logger::debug("Edge " + std::to_string(to) + " -> " + std::to_string(from) + " not found", __CONTEXT__);
        return false;
    }

    res = false;

    for (int i = 0; i < this->adjListDirected[from].size(); i++) {
        if (this->adjListDirected[from][i] == to) {
            this->adjListDirected[from].erase(this->adjListDirected[from].begin() + i);
            res = true;
        }
    }

    if (!res) {
        Logger::debug("Edge " + std::to_string(from) + " -> " + std::to_string(to) + " not found", __CONTEXT__);
        return false;
    }

    return res;
}

bool Graph::isEdge(int from, int to) const {
    for (int i = 0; i < this->adjList[from].size(); i++) {
        if (this->adjList[from][i] == to) {
            return true;
        }
    }

    return false;
}

int Graph::degres(int vertex) {
    return this->adjList[vertex].size();
}

std::vector<int> Graph::BFS(int start) {
    Logger::debug("BFS algorithm starting...", __CONTEXT__);

    std::vector<Color> color = std::vector<Color>(this->size(), Color::BLUE);
    std::vector<int> parent = std::vector<int>(this->size(), -1);
    std::vector<int> res;

    this->BFSVisit(start, color, parent, res);
    for (int v = 0; v < this->size(); v++) {
        if (color[v] == Color::BLUE) {
            this->BFSVisit(v, color, parent, res);
        }
    }

    return res;
}

void Graph::BFSVisit(int vertex, std::vector<Color> &color, std::vector<int> &parent, std::vector<int> &res) {
    std::queue<int> q;
    color[vertex] = Color::WHITE;
    q.push(vertex);
    while (!q.empty()) {
        int w = q.front();
        q.pop();
        for (int z : this->adjList[w]) {
            if (color[z] == Color::BLUE) {
                color[z] = Color::WHITE;
                parent[z] = w;
                q.push(z);
            }
        }
        color[w] = Color::RED;
        res.push_back(w);
    }
}

std::vector<int> Graph::DFS(int start, typeOfOutput type) {
    Logger::debug("DFS algorithm starting...", __CONTEXT__);

    std::vector<Color> color = std::vector<Color>(this->size(), Color::BLUE);
    std::vector<int> parent = std::vector<int>(this->size(), -1);
    std::vector<int> res;

    this->DFSVisit(start, color, parent, res, type);
    for (int v = 0; v < this->size(); v++) {
        if (color[v] == Color::BLUE) {
            this->DFSVisit(v, color, parent, res, type);
        }
    }
    return res;
}

void Graph::DFSVisit(int vertex, std::vector<Color> &color, std::vector<int> &parent, std::vector<int> &res,
                     typeOfOutput type) {
    color[vertex] = Color::WHITE;
    if (type == typeOfOutput::PREORDER) {
        res.push_back(vertex);
    }
    for (int w : this->adjList[vertex]) {
        if (color[w] == Color::BLUE) {
            parent[w] = vertex;
            this->DFSVisit(w, color, parent, res, type);
        }
    }
    color[vertex] = Color::RED;
    if (type == typeOfOutput::POSTORDER) {
        res.push_back(vertex);
    }
}

Graph Graph::createRandomGraph(int numberOfVertices, double edgeProbability) {
    Logger::debug("Creating random graph with " + std::to_string(numberOfVertices) + " vertices and edge probability " + std::to_string(edgeProbability) + "...", __CONTEXT__);

    if (numberOfVertices <= 0 || edgeProbability < 0.0 || edgeProbability > 1.0) {
        throw std::invalid_argument("Invalid input parameters.");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> edgeDist(0.0, 1.0);

    Graph g = Graph(numberOfVertices);
    for (int i = 0; i < numberOfVertices; i++) {
        for (int j = i + 1; j < numberOfVertices; j++) {
            if (edgeDist(gen) < edgeProbability) {
                g.addEdge(i, j);
            }
        }
    }

    Logger::info("Random graph created with " + LogColor::fgBrightRed + std::to_string(g.size()) + LogColor::reset + " vertex and " + LogColor::fgBrightRed + std::to_string(g.m()) + LogColor::reset + " edge.", __CONTEXT__);

    return g;
}

void Graph::print() {
    Logger::debug("Printing graph...", __CONTEXT__);

    for (int i = 0; i < this->size(); i++) {
        std::cout << i << " -> ";
        for (int j : this->adjList[i]) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
}

bool Graph::isBipartite() {
    Logger::debug("Bipartite algorithm starting...", __CONTEXT__);
    std::vector<Color> color = std::vector<Color>(this->size(), Color::BLUE);
    std::vector<Color> partie = std::vector<Color>(this->size(), Color::NONE);
    std::vector<int> parent = std::vector<int>(this->size(), -1);

    for (int v = 0; v < this->size(); v++) {
        if (color[v] == Color::BLUE) {
            partie[v] = Color::BLUE;
            bool res = this->isBipartiteVisit(v, color, parent, partie);
            if (!res) {
                return false;
            }
        }
    }
    return true;
}

bool
Graph::isBipartiteVisit(int vertex, std::vector<Color> &color, std::vector<int> &parent, std::vector<Color> &partie) {
    std::queue<int> q;
    color[vertex] = Color::WHITE;
    q.push(vertex);
    while (!q.empty()) {
        int w = q.front();
        q.pop();
        Color nextColor = partie[w] == Color::BLUE ? Color::RED : Color::BLUE;
        for (int z : this->adjList[w]) {

            // PART TO CHECK IF THE GRAPH IS BIPARTITE
            if (partie[z] != Color::NONE) {
                if (partie[z] == partie[w]) {
                    return false;
                }
            } else {
                partie[z] = nextColor;
            }

            if (color[z] == Color::BLUE) {
                color[z] = Color::WHITE;
                parent[z] = w;
                q.push(z);
            }
        }
        color[w] = Color::RED;
    }
    return true;
}

