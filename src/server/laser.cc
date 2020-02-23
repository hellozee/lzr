#include "laser.hh"
#include <algorithm>
#include <chrono>
#include <thread>

void
lzr::laser::set_power(unsigned int power)
{
    // power should be between 1-100
    m_power = std::clamp(power, min_power, max_power);
}

auto
lzr::laser::power() const -> unsigned int
{
    return m_power;
}

auto
lzr::laser::keep_alive() -> error
{
    // there are random segfaults here and there,
    // not able to debug them for now
    if (m_emitting) {
        stop_emission();
        start_emission();
        return false;
    }

    return true;
}

auto
lzr::laser::start_emission() -> error
{
    if (!m_emitting) {
        m_emitting = true;

        auto callback_fn = [this](const std::error_code&) { this->stop_emission(); };

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

auto
lzr::laser::stop_emission() -> error
{
    if (m_emitting) {
        m_emitting = false;
        m_timer->cancel();
        return false;
    }
    return true;
}

auto
lzr::laser::is_emitting() const -> bool
{
    return m_emitting;
}