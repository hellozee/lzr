add_executable(client main.cc client.cc repl.cc) 
target_link_libraries(client pthread)
