add_executable(server main.cc server.cc laser.cc commander.cc)
target_link_libraries(server pthread absl::strings)
