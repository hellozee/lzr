#ifndef _LZR_LASER_HH_
#define _LZR_LASER_HH_

#include "timer.hh"

namespace lzr {
    class laser {
        using error = bool;
private:
        unsigned int m_power = 1;
        bool m_emitting      = false;
        lzr::timer m_timer;
        const unsigned int max_power = 100;
        const unsigned int min_power = 1;
        const unsigned int delay     = 5;

public:
        void
        set_power(unsigned int power)
        {
            // power should be between 1-100
            m_power = power > max_power ? max_power : power < min_power ? min_power : power;
        }

        auto
        power() -> unsigned int
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
                m_timer.reset();
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

                auto callback_fn = [&](){
                    m_emitting = false;
                };

                m_timer.set_timeout(delay, callback_fn);
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
                m_timer.stop();
                return false;
            }
            return true;
        }

        auto
        is_emitting() -> bool
        {
            return m_emitting;
        }
    };
}// namespace lzr
#endif // _LZR_LASER_HH_
