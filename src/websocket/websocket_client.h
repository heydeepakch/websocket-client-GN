#pragma once
#include <string>
#include <vector>
#include <memory>

class WebSocketImpl;

class WebSocketClient {
public:
    explicit WebSocketClient(bool use_tls);
    ~WebSocketClient();
    void connect(const std::string& host,
                 const std::string& port,
                 const std::string& path);

    void sendText(const std::string& message);
    std::string receive();
    void close();

private:
    bool use_tls_;
    std::unique_ptr<WebSocketImpl> impl_;
};
