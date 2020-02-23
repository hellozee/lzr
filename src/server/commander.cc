#include "commander.hh"

lzr::commander::commander()
{
    // really neat, isn't it? :P
    m_worker["STR"] = &commander::command_str;
    m_worker["STP"] = &commander::command_stp;
    m_worker["ST?"] = &commander::command_st;
    m_worker["KAL"] = &commander::command_kal;
    m_worker["PW?"] = &commander::command_pwq;
    m_worker["PW="] = &commander::command_pws;
}

auto
lzr::commander::execute(const std::string& command, const std::vector<std::string>& args) -> std::string const
{
    auto iterator = m_worker.find(command);

    if (iterator != m_worker.end()) {
        return command + iterator->second(this, args);
    }
    return std::string("UK!");
}

auto
lzr::commander::command_str(const std::vector<std::string>& args) -> std::string const
{
    if (!args.empty()) {
        throw std::invalid_argument("Invalid Argument(s)");
    }

    auto error = m_laser.start_emission();

    if (error) {
        return failure;
    }

    return success;
}

auto
lzr::commander::command_stp(const std::vector<std::string>& args) -> std::string const
{
    if (!args.empty()) {
        throw std::invalid_argument("Invalid Argument(s)");
    }

    auto error = m_laser.stop_emission();

    if (error) {
        return failure;
    }

    return success;
}

auto
lzr::commander::command_st(const std::vector<std::string>& args) -> std::string const
{
    if (!args.empty()) {
        throw std::invalid_argument("Invalid Argument(s)");
    }

    auto emitting = m_laser.is_emitting() ? std::string("1") : std::string("0");
    return "|" + emitting + success;
}

auto
lzr::commander::command_kal(const std::vector<std::string>& args) -> std::string const
{
    if (!args.empty()) {
        throw std::invalid_argument("Invalid Argument(s)");
    }

    auto error = m_laser.keep_alive();

    if (error) {
        return failure;
    }

    return success;
}

auto
lzr::commander::command_pwq(const std::vector<std::string>& args) -> std::string const
{
    if (!args.empty()) {
        throw std::invalid_argument("Invalid Argument(s)");
    }

    unsigned int power = 0;

    if (m_laser.is_emitting()) {
        power = m_laser.power();
    }

    return "|" + std::to_string(power) + success;
}

auto
lzr::commander::command_pws(const std::vector<std::string>& args) -> std::string const
{
    if (m_laser.is_emitting() && args.size() == 1) {
        int power = 0;
        try {
            power = std::stoi(args.at(0));
        } catch (std::exception& e) {
            throw e;
        }
        m_laser.set_power(power);
        return success;
    }

    throw std::invalid_argument("Invalid Argument(s)");
}