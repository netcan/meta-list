cmake_minimum_required(VERSION 3.0)
project(value_list)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party
        )

add_executable(value_list_ut
        test/ut/test_value_list.cpp
        include/value-list/value_list_ns.hpp
        include/value-list/types/value_list_t.hpp
        include/value-list/types/type_c.hpp
        include/value-list/types/value_c.hpp
        third_party/catch_amalgamated.cpp
        include/value-list/types/dispatch_value.hpp include/value-list/algo/pipe_adapter.hpp include/value-list/algo/filter.hpp include/value-list/concept/list.hpp include/value-list/algo/fold_left.hpp include/value-list/algo/append.hpp include/value-list/algo/prepend.hpp include/value-list/concept/value_or_type.hpp include/value-list/algo/concat.hpp include/value-list/algo/partition.hpp)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
target_link_libraries(value_list_ut stdc++ m)
endif()