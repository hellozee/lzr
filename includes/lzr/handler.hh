#ifndef _lzr_handler_hh_
#define _lzr_handler_hh_

#include <asio.hpp>
#include <string>

namespace lzr {
    class handler {
        public:
        static auto
        get_data(asio::ip::tcp::socket& sock) -> std::string
        {
            asio::streambuf buf;
            try {
                asio::read_until(sock, buf, '\n');
            } catch (std::exception& e) {
                return "";
            }
            auto data = asio::buffer_cast<const char*>(buf.data());
            return data;
        }

        static void
        send_data(asio::ip::tcp::socket& sock, const std::string& msg)
        {
            asio::write(sock, asio::buffer(msg + "\n"));
        }
    };
};

#endif
