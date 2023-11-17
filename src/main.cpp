#include "model/iofile.hpp"

int main(int argc, char** argv) {
    Logger::setLogLevel(LogLevel::DEBUG);

    Logger::info(LogColor::fgMagenta + "STARTING PROGRAM" + LogColor::reset, __CONTEXT__);

//    std::string filename = "first_test";
//    std::string filename = "random";
    std::string filename = "test";

//    Graph g = iofile::readFile(filename);
    Graph g = Graph::createRandomGraph(100, .001);

    iofile::writeResultFile(filename, g, "exact");
//    iofile::writeResultFile(filename, g, "constructive");
//    iofile::writeInputFile(filename, g);

    Logger::info(LogColor::fgMagenta + "PROGRAM ENDED" + LogColor::reset, __CONTEXT__);

    return 0;
}
