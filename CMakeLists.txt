cmake_minimum_required(VERSION 3.0)

set(PROJECT_NAME lzr)
project(${PROJECT_NAME})

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )

set(CMAKE_CXX_STANDARD 17)

if( "${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    find_program(
        CLANG_TIDY_EXE
        NAMES "clang-tidy"
        DOC "Path to clang-tidy executable"
    )

    if(CLANG_TIDY_EXE)
        set(CMAKE_CXX_CLANG_TIDY 
            clang-tidy
            --header-filter=.
            --checks=*,-fuchsia-default-arguments-calls,-fuchsia-trailing-return,-llvm-header-guard)
    endif()
    
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
      set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Weverything")
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
      set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
      set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /W4 /WX")
    endif()
endif()

set(SOURCES src/main.cc)

add_executable( ${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} pthread)
