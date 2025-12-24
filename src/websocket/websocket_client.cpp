#include "websocket_client.h"

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>

using tcp = boost::asio::ip::tcp;
namespace websocket = boost::beast::websocket;

class WebSocketImpl {
public:
    boost::asio::io_context ioc;
    tcp::resolver resolver{ioc};
    websocket::stream<tcp::socket> ws{ioc};
};

WebSocketClient::WebSocketClient(bool use_tls)
    : use_tls_(use_tls), impl_(new WebSocketImpl) {}

WebSocketClient::~WebSocketClient() = default;

void WebSocketClient::connect(const std::string& host,
                              const std::string& port,
                              const std::string& path) {
    auto const results = impl_->resolver.resolve(host, port);
    boost::asio::connect(impl_->ws.next_layer(), results);
    impl_->ws.handshake(host, path);
}

void WebSocketClient::sendText(const std::string& message) {
    impl_->ws.write(boost::asio::buffer(message));
}

std::string WebSocketClient::receive() {
    boost::beast::flat_buffer buffer;
    impl_->ws.read(buffer);
    return boost::beast::buffers_to_string(buffer.data());
}

void WebSocketClient::close() {
    impl_->ws.close(websocket::close_code::normal);
}
