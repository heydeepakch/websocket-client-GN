#pragma once
#include <string>

struct CLIOptions {
    std::string url;
    bool binary = false;
    bool verbose = false;
};

CLIOptions parseCLI(int argc, char* argv[]);
