#ifndef _lzr_client_hh_
#define _lzr_client_hh_

#include <asio.hpp>
#include <string>

namespace lzr {
    class client {
        public:
        client(std::string server_ip);
        void send(const std::string& msg);
        std::string receive();

        private:
        asio::io_context m_iocontext;
        asio::ip::tcp::socket m_socket;
    };
}

#endif
