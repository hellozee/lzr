add_executable(lzr-server main.cc server.cc laser.cc commander.cc)
target_link_libraries(lzr-server  Threads::Threads absl::strings asio::asio)
