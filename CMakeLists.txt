cmake_minimum_required(VERSION 3.0)

# Initial Setup ============================================

set(PROJECT_NAME lzr)
project(${PROJECT_NAME})

set( CMAKE_BUILD_TYPE Debug)
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )

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

# Building docs =============================================

if (CMAKE_BUILD_TYPE MATCHES "^[Rr]elease")
	option(BUILD_DOC "Build documentation" ON)
	set(DOXYGEN_SKIP_DOT false)

	find_package(Doxygen)
	if (DOXYGEN_FOUND)

	    set(DOXYGEN_IN docs/Doxyfile.in)
	    set(DOXYGEN_OUT ${CMAKE_BINARY_DIR}/docs/Doxyfile)

	    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

	    add_custom_target( docs ALL
		COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		VERBATIM )

	else (DOXYGEN_FOUND)
	  message("Doxygen not installed")
	endif (DOXYGEN_FOUND)
endif()
