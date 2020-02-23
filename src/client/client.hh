#ifndef _lzr_client_hh_
#define _lzr_client_hh_

#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>
#include <string>

namespace lzr {
    class client {
        public:
        client(const std::string& server_ip);
        void send(const std::string& msg);
        std::string receive();

        private:
        asio::io_context m_iocontext;
        asio::ip::tcp::socket m_socket;
    };
}

#endif // _lzr_client_hh_
