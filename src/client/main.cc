#include "repl.hh"

auto
main(int argc, char const* argv[]) -> int
{
    if (argc != 2) {
        std::cout << "Usage :" << std::endl
                  << "\tlzr-client <server-ip>" << std::endl
                  << "\tExample: lzr-client 127.0.0.1" << std::endl;
        return -1;
    }

    try {
        lzr::repl laser_repl(argv[1]);
        laser_repl.run();
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
