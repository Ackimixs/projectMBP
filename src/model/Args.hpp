#pragma once

#include "../model/iofile.hpp"

void readArgs(std::map <std::string, std::vector<std::string>> &args);

void runGraphAlgoArgs(std::map<std::string, std::vector<std::string>> &args);

void runGraphRandomArgs(std::map<std::string, std::vector<std::string>> &args);
