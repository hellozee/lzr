#ifndef _lzr_repl_hh_
#define _lzr_repl_hh_

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
#endif // _lzr_repl_hh_
