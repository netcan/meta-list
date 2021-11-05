//
// Created by netcan on 2021/11/5.
//

#include <catch_amalgamated.hpp>
#include <value-list/types/value_list_t.h>
#include <value-list/types/type_c.h>
#include <value-list/algo/transform.h>

using namespace VALUE_LIST_NS;

template<typename...> struct dump;

TEST_CASE("value_list") {
    constexpr auto vl = value_list<1, 2, 3, 4>;
}

TEST_CASE("transform: calculate value") {
    constexpr auto vl = value_list<1, 2, 3, 4>;
    constexpr auto result = transform(vl, [](auto x) {
        return x * 2;
    });
    static_assert(result == value_list<2, 4, 6, 8>);
}

TEST_CASE("transform: calculate type") {
    constexpr auto vl = value_list<tc<int>, tc<char>, tc<double>>;
    constexpr auto result = transform(vl, []<typename T>(TypeConst <T>) {
        return tc < std::add_pointer_t<T>>;
    });
    static_assert(result == value_list<tc<int*>, tc<char*>, tc<double*>>);
}
