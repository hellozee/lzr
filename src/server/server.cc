#include "server.hh"
#include <absl/strings/str_split.h>
#include <lzr/handler.hh>

using asio::ip::tcp;

lzr::server::server()
    : m_acceptor(m_iocontext, tcp::endpoint(tcp::v4(), 4242))
    , m_socket(m_iocontext)
{
    m_acceptor.accept(m_socket);
}

void
lzr::server::run()
{
    while (true) {
        auto msg = lzr::handler::get_data(m_socket);

        if (msg.empty()) {
            break;
        }

        msg.pop_back();
        std::vector<std::string> args = absl::StrSplit(msg, "|");
        auto command                  = args.at(0);
        args                          = std::vector<std::string>(args.begin() + 1, args.end());

        try {
            msg = m_commander.execute(command, args);
        } catch (std::exception& e) {
            msg = msg + "!";
        }

        lzr::handler::send_data(m_socket, msg);
    }
}