#include <iostream>
#include "cli/cli.h"

int main(int argc, char* argv[]) {
    CLIOptions options = parseCLI(argc, argv);

    std::cout << "URL     : " << options.url << "\n";
    std::cout << "Binary  : " << (options.binary ? "true" : "false") << "\n";
    std::cout << "Verbose : " << (options.verbose ? "true" : "false") << "\n";

    return 0;
}
