#ifndef _lzr_commander_hh_
#define _lzr_commander_hh_

#include "laser.hh"
#include <functional>
#include <map>
#include <string>
#include <vector>

namespace lzr {
    class commander {
        private:
        typedef const std::vector<std::string> strvec;
        std::unordered_map<std::string, std::function<std::string(commander*, strvec&)>> m_worker;
        lzr::laser m_laser;
        const std::string success = "#";
        const std::string failure = "!";

        public:
        commander();
        std::string const execute(const std::string& command, strvec& args);

        private:
        std::string const command_str(strvec& args);
        std::string const command_stp(strvec& args);
        std::string const command_st(strvec& args);
        std::string const command_kal(strvec& args);
        std::string const command_pwq(strvec& args);
        std::string const command_pws(strvec& args);
    };
} // namespace lzr
#endif // _lzr_commander_hh_
