#ifndef _LZR_TIMER_HH_
#define _LZR_TIMER_HH_

#include <chrono>
#include <functional>
#include <thread>

namespace lzr {
    /* lzr::timer class adapted from https://gist.github.com/mcleary/b0bf4fa88830ff7c882d
     * feels like a hack, but it works, could be a bit inaccurate, using milliseconds
     * should be better, anyway, if available always use QTimer, far far far better.
     */
    class timer {
        bool m_running = false, m_reset = false;

public:
        void
        set_timeout(unsigned int delay, const std::function < void(void) > &callback)
        {
            m_running = true;
            auto timer_fn = [ = ](){
                auto start = std::chrono::system_clock::now();
                auto end   = std::chrono::system_clock::now();

                while (std::chrono::duration_cast < std::chrono::seconds > (end - start).count() < delay && m_running) {
                    if (m_reset) {
                        start   = std::chrono::system_clock::now();
                        m_reset = false;
                    }
                    end = std::chrono::system_clock::now();
                }

                callback();
            };

            std::thread t(timer_fn);
            t.detach();
        }

        void
        stop()
        {
            m_running = false;
        }

        void
        reset()
        {
            // should perform whether it is running or not but I already
            // do this in lzr::laser::keep_alive, so would be redundant
            m_reset = true;
        }
    };
}// namespace lzr
#endif // _LZR_TIMER_HH_
