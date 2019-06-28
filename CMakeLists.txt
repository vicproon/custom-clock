project(custom-clock)
cmake_minimum_required(VERSION 3.0)

add_executable(custom-clock-test src/main.cpp custom_clock.hpp)

target_include_directories(custom-clock-test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(custom-clock-test PRIVATE -std=c++11 -O2)
