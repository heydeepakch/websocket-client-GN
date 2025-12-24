#include "cli/cli.h"
#include "websocket/websocket_client.h"
#include <iostream>

int main(int argc, char* argv[]) {
    auto options = parseCLI(argc, argv);

    WebSocketClient client(false);

    client.connect("echo.websocket.events", "80", "/");

    std::string msg = "Hello WebSocket!";
    client.sendText(msg);

    std::string reply = client.receive();
    std::cout << "Received: " << reply << std::endl;

    client.close();
}
