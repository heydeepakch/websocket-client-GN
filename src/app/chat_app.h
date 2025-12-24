#pragma once
#include "cli/cli.h"
#include "websocket/websocket_client.h"

class ChatApp {
public:
    explicit ChatApp(const CLIOptions& options);
    void run();

private:
    CLIOptions options_;
    WebSocketClient client_;
};
