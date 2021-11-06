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
        include/value-list/types/value_c.h
        third_party/catch_amalgamated.cpp
        include/value-list/types/dispatch_value.h include/value-list/algo/pipe_adapter.h include/value-list/algo/filter.h include/value-list/concept/list.h include/value-list/algo/fold_left.h include/value-list/algo/append.h include/value-list/algo/prepend.h include/value-list/concept/value_or_type.h)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
target_link_libraries(value_list_ut stdc++ m)
endif()