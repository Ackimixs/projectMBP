#pragma once

#include <filesystem>

#include "../model/iofile.hpp"

void readArgs(std::map <std::string, std::vector<std::string>> &args, int argc, char** argv);

void runGraphAlgoArgs(std::map<std::string, std::vector<std::string>> &args, const std::string& algoName);

void runGraphRandomArgs(std::map<std::string, std::vector<std::string>> &args);

void runGraphTestAlgo(std::map<std::string, std::vector<std::string>> &args, const std::string& algoName);