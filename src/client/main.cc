#include "repl.hh"

auto
main(int argc, char const* argv[]) -> int
{
    lzr::repl laser_repl("127.0.0.1");
    laser_repl.run();
    return 0;
}
