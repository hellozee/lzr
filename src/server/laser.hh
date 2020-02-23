#ifndef _LZR_LASER_HH_
#define _LZR_LASER_HH_

#include <asio/io_context.hpp>
#include <asio/steady_timer.hpp>
#include <iostream>
#include <memory>

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
        void set_power(unsigned int power);
        unsigned int power() const;

        /* lzr::laser::keep_alive reset's the laser timer back to original delay.
         * Returns a bool to determine whether there was error or not.
         */
        error keep_alive();

        /* lzr::laser::start_emission starts emission if the laser is not emitting.
         * Returns a bool to determine whether there was error or not.
         * Using std::optional seems a good idea here.
         */
        error start_emission();

        /* Exact opposite of lzr::laser::start_emission
         */
        error stop_emission();
        bool is_emitting() const;
    };
} // namespace lzr
#endif // _LZR_LASER_HH_
