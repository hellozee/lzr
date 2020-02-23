add_executable(lzr-server main.cc server.cc laser.cc commander.cc)
target_link_libraries(lzr-server pthread absl::strings)
