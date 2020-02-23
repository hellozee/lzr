#ifndef _LZR_REPL_HH_
#define _LZR_REPL_HH_

#include "client.hh"
#include <iostream>

namespace lzr {
    enum class mode { normal, silly };

    class repl {
        private:
        lzr::mode m_mode = lzr::mode::normal;
        lzr::client m_client;

        public:
        repl(std::string server_ip);
        void run();
    };
} // namespace lzr
#endif // _LZR_REPL_HH_
