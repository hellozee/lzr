cmake_minimum_required(VERSION 3.0)

set(PROJECT_NAME lzr)
project(${PROJECT_NAME})

set( CMAKE_BUILD_TYPE Debug)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )

set(CMAKE_CXX_STANDARD 17)

set(SOURCES src/main.cc)

add_executable( ${PROJECT_NAME} ${SOURCES})

if( "${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    if ("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
      target_compile_options(${PROJECT_NAME} -Weverything -pedantic)
    elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
      target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
    elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
      target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
    endif()
endif()
