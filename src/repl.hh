#ifndef _LZR_REPL_HH_
#define _LZR_REPL_HH_

#include "commander.hh"
#include <iostream>
#include <sstream>
#include <tuple>

namespace lzr {
    enum class mode { normal, silly };

    class repl {
        private:
        lzr::commander m_commander;
        lzr::mode m_mode = lzr::mode::normal;

        public:
        void
        run()
        {
            std::string input;
            while (true) {
                std::cout << ">> ";
                std::cin >> input;

                if (m_mode == mode::silly) {
                    input = std::string(input.rbegin(), input.rend());
                }

                if (input == "ESM") {
                    m_mode = mode::silly;
                    continue;
                }

                if (input == "DSM") {
                    m_mode = mode::normal;
                    continue;
                }

                std::string output;

                try {
                    auto [command, args] = get_args(input);
                    output               = m_commander.execute(command, args);
                } catch (const std::exception& /*unused*/) {
                    output = input + "!";
                }

                std::cout << output << std::endl;
            }
        }

        private:
        /* lzr::repl::get_args takes the input and returns the `int` arguments
         * as a vector without the command itself. Use boost/qt if available.
         * Adapted from https://www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c/
         */
        static auto
        get_args(const std::string& input) -> std::tuple<std::string, std::vector<unsigned int>>
        {
            std::vector<unsigned int> args;
            std::string arg;
            std::string command;
            std::istringstream stream(input);

            bool is_command = true;

            while (std::getline(stream, arg, '|')) {
                if (is_command) {
                    is_command = false;
                    command    = arg;
                    continue;
                }

                try {
                    auto a = std::stoi(arg);
                    if (a < 1) {
                        throw std::runtime_error("Invalid arguments!");
                    }
                    args.push_back(static_cast<unsigned int>(a));
                } catch (const std::exception& e) {
                    /* instead of throwing an exception we could
                     * return an error value using something like
                     * std::variant or std::optional, honestly not
                     * a big fan of exceptions
                     */
                    throw e;
                }
            }
            return { command, args };
        }
    };
} // namespace lzr
#endif // _LZR_REPL_HH_
