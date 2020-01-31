#pragma once

#include <thread>
#include <chrono>
#include <functional>

namespace lzr {
    /* time class adapted from https://gist.github.com/mcleary/b0bf4fa88830ff7c882d
     * feels like a hack, but it works, could be a bit inaccurate, using milliseconds
     * should be better, anyway, if available always use QTimer, far far far better.
     */
    class timer {
        bool m_running = false, m_reset = false;

public:
        void 
        set_timeout(int delay, std::function < void(void) > callback)
        {
            m_running = true;
            std::thread t([ = ](){
                auto start = std::chrono::system_clock::now();
                auto end   = std::chrono::system_clock::now();

                while (std::chrono::duration_cast < std::chrono::seconds > (end - start).count() < delay) {
                    if (!m_running) {
                        callback();
                        return;
                    }

                    if (m_reset) {
                        start   = std::chrono::system_clock::now();
                        m_reset = false;
                    }

                    end = std::chrono::system_clock::now();
                }

                callback();
            });
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
}
