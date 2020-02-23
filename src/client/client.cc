#include "client.hh"
#include <lzr/handler.hh>

using asio::ip::tcp;

lzr::client::client(const std::string& server_ip)
    : m_socket(tcp::socket(m_iocontext))
{
    m_socket.connect(tcp::endpoint(asio::ip::make_address(server_ip), 4242));
}

void
lzr::client::send(const std::string& message)
{
    lzr::handler::send_data(m_socket, message);
}

auto
lzr::client::receive() -> std::string
{
    return lzr::handler::get_data(m_socket);
}