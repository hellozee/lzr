add_executable(lzr-client main.cc client.cc repl.cc) 
target_link_libraries(lzr-client pthread)
