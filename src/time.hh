#pragma once

#include <thread>
#include <chrono>
#include <functional>

namespace lzr{
    class timer {
    bool m_running = false, m_reset = false;

    public:
        void 
        set_timeout(int delay, std::function<void(void)> callback)
        {
            m_running = true;
            std::thread t([=]() {
                auto start = std::chrono::system_clock::now();
                auto end = std::chrono::system_clock::now();
                while(std::chrono::duration_cast<std::chrono::seconds>(end - start).count() < delay){
                    if(!m_running){
                        callback();
                        break;
                    }
                    
                    if(m_reset){
                        start = std::chrono::system_clock::now();
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
            m_reset = true;
        }
    };
}
