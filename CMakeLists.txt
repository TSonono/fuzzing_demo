cmake_minimum_required(VERSION 3.0)
project(fuzz_demo)

add_subdirectory(src)

add_executable(fuzz_entry fuzz/test.c)

target_include_directories(fuzz_entry
    PUBLIC include)

target_link_libraries(fuzz_entry udp)