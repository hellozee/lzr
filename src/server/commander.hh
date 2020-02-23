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
        typedef std::vector<std::string> const& strvec;
        std::unordered_map<std::string, std::function<std::string(commander*, strvec)>> m_worker;
        lzr::laser m_laser;
        std::string const success = "#";
        std::string const failure = "!";

        public:
        commander();
        std::string execute(std::string const& command, strvec args);

        private:
        std::string const command_str(strvec args);
        std::string const command_stp(strvec args);
        std::string const command_st(strvec args) const;
        std::string const command_kal(strvec args);
        std::string const command_pwq(strvec args) const;
        std::string const command_pws(strvec args);
    };
} // namespace lzr
#endif // _lzr_commander_hh_
