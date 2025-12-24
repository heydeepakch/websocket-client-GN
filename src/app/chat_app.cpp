#include "chat_app.h"
#include <iostream>

ChatApp::ChatApp(const CLIOptions& options)
    : options_(options),
      client_(options.url.starts_with("wss://")) {}

void ChatApp::run() {
    std::string host = options_.url.substr(options_.url.find("://") + 3);
    std::string port = client_.isTLS() ? "443" : "80";

    client_.connect(host, port, "/");

    // Read and display the initial server message
    try {
        std::string welcome = client_.receive();
        std::cout << "Server: " << welcome << std::endl;
    } catch (...) {
        // Some servers don't send an initial message, that's ok
    }

    std::cout << "\nConnected. Type messages (type 'exit' to quit):\n";

    while (true) {
        std::string input;
        std::getline(std::cin, input);

        if (input == "exit") break;

        client_.sendText(input);
        std::string reply = client_.receive();

        std::cout << "Echo: " << reply << std::endl;
    }

    client_.close();
}
