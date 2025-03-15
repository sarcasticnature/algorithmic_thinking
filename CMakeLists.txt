cmake_minimum_required(VERSION 3.14)
project(algorithmic_thinking)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic")

configure_file(test.sh ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

option(ENABLE_TESTS "Enable tests" ON)
if (${ENABLE_TESTS})
  enable_testing()
endif()

add_subdirectory(chapter_1)
