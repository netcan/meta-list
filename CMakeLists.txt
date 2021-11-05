cmake_minimum_required(VERSION 3.0)
project(value_list)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party
        )

add_executable(value_list_ut
        test/ut/test_value_list.cpp
        include/value-list/value_list_ns.h
        include/value-list/types/value_list_t.h
        include/value-list/types/type_c.h
        third_party/catch_amalgamated.cpp
        )

