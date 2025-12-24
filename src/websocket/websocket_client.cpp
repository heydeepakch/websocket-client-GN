#include "websocket_client.h"

WebSocketClient::WebSocketClient(bool use_tls)
    : use_tls_(use_tls) {}

void WebSocketClient::connect(const std::string&, const std::string&, const std::string&) {}
void WebSocketClient::sendText(const std::string&) {}
void WebSocketClient::sendBinary(const std::vector<uint8_t>&) {}
std::string WebSocketClient::receive() { return {}; }
void WebSocketClient::close() {}
