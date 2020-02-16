#ifndef _LZR_LASER_HH_
#define _LZR_LASER_HH_

#include <algorithm>
#include <asio/io_context.hpp>
#include <asio/steady_timer.hpp>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

namespace lzr {
    class laser {
        using error = bool;

        private:
        std::unique_ptr<asio::steady_timer> m_timer;
        std::unique_ptr<asio::io_context> m_context;
        unsigned int m_power         = 1;
        bool m_emitting              = false;
        unsigned int const max_power = 100;
        unsigned int const min_power = 1;
        unsigned int const delay     = 5;

        public:
        void
        set_power(unsigned int power)
        {
            // power should be between 1-100
            m_power = std::clamp(power, min_power, max_power);
        }

        auto
        power() -> unsigned int const
        {
            return m_power;
        }

        /* lzr::laser::keep_alive reset's the laser timer back to original delay.
         * Returns a bool to determine whether there was error or not.
         */
        auto
        keep_alive() -> error
        {
            if (m_emitting) {
                stop_emission();
                start_emission();
                return false;
            }

            return true;
        }

        /* lzr::laser::start_emission starts emission if the laser is not emitting.
         * Returns a bool to determine whether there was error or not.
         * Using std::optional seems a good idea here.
         */
        auto
        start_emission() -> error
        {
            if (!m_emitting) {
                m_emitting = true;

                auto callback_fn = [this](const std::error_code& ec) { this->m_emitting = false; };

                // Why am I feeling I am doing something wrong here?
                m_context = std::make_unique<asio::io_context>();
                m_timer   = std::make_unique<asio::steady_timer>(*m_context, std::chrono::seconds(delay));
                m_timer->async_wait(callback_fn);
                std::thread t([this]() { this->m_context->run(); });
                t.detach();
                return false;
            }
            return true;
        }

        /* Exact opposite of lzr::laser::start_emission
         */
        auto
        stop_emission() -> error
        {
            if (m_emitting) {
                m_emitting = false;
                m_timer->cancel();
                return false;
            }
            return true;
        }

        auto
        is_emitting() -> bool const
        {
            return m_emitting;
        }
    };
} // namespace lzr
#endif // _LZR_LASER_HH_
