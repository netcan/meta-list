cmake_minimum_required(VERSION 3.0)
project(value_list)

set(CMAKE_CXX_STANDARD 20)

set(META_VALUE_LIST_INC
        include/value-list/value_list_ns.hpp
        include/value-list/types/value_list_t.hpp
        include/value-list/types/type_c.hpp
        include/value-list/types/value_c.hpp
        include/value-list/types/dispatch_value.hpp
        include/value-list/algo/pipe_adapter.hpp
        include/value-list/algo/filter.hpp
        include/value-list/concept/list.hpp
        include/value-list/algo/fold_left.hpp
        include/value-list/algo/append.hpp
        include/value-list/algo/prepend.hpp
        include/value-list/concept/value_or_type.hpp
        include/value-list/algo/concat.hpp
        include/value-list/algo/partition.hpp
        include/value-list/algo/contain.hpp
        include/value-list/algo/unique.hpp include/value-list/types/pair_c.hpp include/value-list/algo/enumerate.hpp include/value-list/algo/flatten.hpp include/value-list/type.hpp include/value-list/algo/convert_to.hpp)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party)

add_executable(value_list_ut
        ${META_VALUE_LIST_INC}
        third_party/catch_amalgamated.cpp
        test/ut/test_value_list.cpp)

add_executable(datatable
        ${META_VALUE_LIST_INC}
        examples/datatable.cpp)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
target_link_libraries(value_list_ut stdc++ m)
endif()