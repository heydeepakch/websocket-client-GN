#include "cli.h"
#include <CLI11.hpp>
#include <iostream>

CLIOptions parseCLI(int argc, char* argv[]) {
    CLIOptions options;

    CLI::App app{"C++ WebSocket Client"};

    app.add_option(
        "--url",
        options.url,
        "WebSocket server URL (ws:// or wss://)"
    )->required();

    app.add_flag(
        "--binary",
        options.binary,
        "Send messages as binary frames"
    );

    app.add_flag(
        "--verbose",
        options.verbose,
        "Enable verbose logging"
    );

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) {
        std::exit(app.exit(e));
    }

    return options;
}
