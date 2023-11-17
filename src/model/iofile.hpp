#pragma once

#include "Graph.hpp"
#include "../exact/ExactAlgorithm.hpp"
#include "../constructive/ConstructiveHeuristic.hpp"

#include <fstream>
#include <sstream>

namespace iofile {

    Graph readFile(const std::string& filename);

    void writeResultFile(const std::string& filename, const Graph& g, const std::string& algoName);

    void writeInputFile(const std::string& filename, const Graph& g);
}