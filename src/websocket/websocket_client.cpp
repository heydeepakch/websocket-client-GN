#include "websocket_client.h"

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl.hpp>
#include <openssl/ssl.h>
#include <stdexcept>

using tcp = boost::asio::ip::tcp;
namespace websocket = boost::beast::websocket;
namespace ssl = boost::asio::ssl;

class WebSocketImpl {
public:
    boost::asio::io_context ioc;
    tcp::resolver resolver{ioc};
    ssl::context ssl_ctx{ssl::context::tlsv12_client};

    std::unique_ptr<websocket::stream<tcp::socket>> ws_plain;
    std::unique_ptr<websocket::stream<boost::beast::ssl_stream<tcp::socket>>> ws_tls;
};

WebSocketClient::WebSocketClient(bool use_tls)
    : use_tls_(use_tls), impl_(new WebSocketImpl) {}

WebSocketClient::~WebSocketClient() = default;

void WebSocketClient::connect(const std::string& host,
                              const std::string& port,
                              const std::string& path) {

    auto const results = impl_->resolver.resolve(host, port);

    if (use_tls_) {
        impl_->ssl_ctx.set_default_verify_paths();
        impl_->ssl_ctx.set_verify_mode(ssl::verify_none); // For testing; use verify_peer in production
        
        impl_->ws_tls = std::make_unique<
            websocket::stream<boost::beast::ssl_stream<tcp::socket>>
        >(impl_->ioc, impl_->ssl_ctx);

        auto& stream = *impl_->ws_tls;
        
        // Set SNI (Server Name Indication) - required for most servers
        if (!SSL_set_tlsext_host_name(stream.next_layer().native_handle(), host.c_str())) {
            throw std::runtime_error("Failed to set SNI hostname");
        }
        
        boost::asio::connect(stream.next_layer().next_layer(), results);
        stream.next_layer().handshake(ssl::stream_base::client);
        stream.handshake(host, path);
    }
    else {
        impl_->ws_plain = std::make_unique<websocket::stream<tcp::socket>>(impl_->ioc);
        auto& stream = *impl_->ws_plain;
        boost::asio::connect(stream.next_layer(), results);
        stream.handshake(host, path);
    }
}

void WebSocketClient::sendText(const std::string& msg) {
    if (use_tls_)
        impl_->ws_tls->write(boost::asio::buffer(msg));
    else
        impl_->ws_plain->write(boost::asio::buffer(msg));
}

std::string WebSocketClient::receive() {
    boost::beast::flat_buffer buffer;

    if (use_tls_)
        impl_->ws_tls->read(buffer);
    else
        impl_->ws_plain->read(buffer);

    return boost::beast::buffers_to_string(buffer.data());
}

void WebSocketClient::close() {
    if (use_tls_)
        impl_->ws_tls->close(websocket::close_code::normal);
    else
        impl_->ws_plain->close(websocket::close_code::normal);
}
