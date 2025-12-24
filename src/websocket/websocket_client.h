#pragma once

#include <cstdint>
#include <string>
#include <vector>

class WebSocketClient {
public:
    explicit WebSocketClient(bool use_tls);

    void connect(const std::string& host,
                 const std::string& port,
                 const std::string& path);

    void sendText(const std::string& message);
    void sendBinary(const std::vector<uint8_t>& data);

    std::string receive();

    void close();

private:
    bool use_tls_;
};
