cmake_minimum_required(VERSION 3.0)
project(value_list)

set(CMAKE_CXX_STANDARD 20)

set(META_VALUE_LIST_INC
        include/meta-list/meta_list_ns.hpp
        include/meta-list/types/type_list.hpp
        include/meta-list/types/type_c.hpp
        include/meta-list/types/value_c.hpp
        include/meta-list/types/dispatch_value.hpp
        include/meta-list/algo/pipe_adapter.hpp
        include/meta-list/algo/filter.hpp
        include/meta-list/concept/list.hpp
        include/meta-list/algo/fold_left.hpp
        include/meta-list/algo/append.hpp
        include/meta-list/algo/prepend.hpp
        include/meta-list/concept/value_or_type.hpp
        include/meta-list/algo/concat.hpp
        include/meta-list/algo/partition.hpp
        include/meta-list/algo/contain.hpp
        include/meta-list/algo/unique.hpp include/meta-list/types/pair_c.hpp include/meta-list/type.hpp include/meta-list/algo/convert_to.hpp include/meta-list/algo/convert_from.hpp include/meta-list/algo/is_pred_satisfied.hpp)

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

message("CMAKE_CXX_FLAGS:" ${CMAKE_CXX_FLAGS})

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
target_link_libraries(value_list_ut stdc++ m)
endif()