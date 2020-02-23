#include "server.hh"

auto
main() -> int
{
    lzr::server laser_server;
    laser_server.run();
    return 0;
}
