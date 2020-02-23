#ifndef _lzr_server_hh_
#define _lzr_server_hh_

#include "commander.hh"
#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>

namespace lzr {
    class server {
        public:
        server();
        void run();

        private:
        asio::io_context m_iocontext;
        asio::ip::tcp::acceptor m_acceptor;
        asio::ip::tcp::socket m_socket;
        lzr::commander m_commander;
    };
}

#endif // _lzr_server_hh_