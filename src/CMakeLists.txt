add_library(udp udp.c)

target_include_directories(udp
    PUBLIC ${CMAKE_SOURCE_DIR}/include)