#pragma once

#include "Algorithm.hpp"

#include <fstream>
#include <ostream>

namespace iofile {

    Graph readFile(const std::string& filename);

    void writeResultFile(const std::string& filename, const Graph& g, const std::string& algoName);

    void writeInputFile(const std::string& filename, const Graph& g);

    void testAlgo(const std::string& algoName);

}