#ifndef _LZR_COMMANDER_HH_
#define _LZR_COMMANDER_HH_

#include <map>
#include <vector>

#include "laser.hh"

namespace lzr {
    class commander {
private:
        std::map < std::string, std::function < std::string(commander *, const std::vector < int > &) >> m_worker;
        lzr::laser m_laser;
        std::string success = "#";
        std::string failure = "!";

public:
        commander()
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
        execute(const std::string &command, const std::vector < int > &args) -> std::string
        {
            auto iterator = m_worker.find(command);

            if (iterator != m_worker.end()) {
                return command + iterator->second(this, args);
            }
            return std::string("UK!");
        }

private:
        auto
        command_str(const std::vector < int >& /*unused*/) -> std::string
        {
            auto error = m_laser.start_emission();

            if (error) {
                return failure;
            }

            return success;
        }

        auto
        command_stp(const std::vector < int >& /*unused*/) -> std::string
        {
            auto error = m_laser.stop_emission();

            if (error) {
                return failure;
            }

            return success;
        }

        auto
        command_st(const std::vector < int >& /*unused*/) -> std::string
        {
            std::string emitting = m_laser.is_emitting() ? std::string("1") : std::string("0");
            return "|" + emitting + success;
        }

        auto
        command_kal(const std::vector < int >& /*unused*/) -> std::string
        {
            auto error = m_laser.keep_alive();

            if (error) {
                return failure;
            }

            return success;
        }

        auto
        command_pwq(const std::vector < int >& /*unused*/) -> std::string
        {
            unsigned int power = 0;

            if (m_laser.is_emitting()) {
                power = m_laser.power();
            }

            return "|" + std::to_string(power) + success;
        }

        auto
        command_pws(const std::vector < int >& args) -> std::string
        {
            if (m_laser.is_emitting() && !args.empty()) {
                m_laser.set_power(args[0]);
                return success;
            }
            return failure;
        }
    };
}// namespace lzr
#endif // _LZR_COMMANDER_HH_
