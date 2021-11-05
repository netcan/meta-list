//
// Created by netcan on 2021/11/5.
//

#include <catch_amalgamated.hpp>
#include <value-list/algo/transform.h>
#include <value-list/types/type_c.h>

using namespace VALUE_LIST_NS;

template<typename...>
struct dump;

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

TEST_CASE("transform: calculate type: add_pointer_t") {
    constexpr auto vl = value_list<t<int>, t<char>, t<double>>;
    constexpr auto result = transform(vl, []<typename T>(TypeConst<T>) {
        return t<std::add_pointer_t<T>>;
    });
    static_assert(result == value_list<t<int*>, t<char*>, t<double*>>);
}

TEST_CASE("transform: calculate type: if constexpr") {
    constexpr auto vl = value_list<1, 2>;
    constexpr auto result = transform(vl, [](auto v) {
        if constexpr (v == 1) {
            return t<char>;
        } else if (v == 2) {
            return t<short>;
        }
    });
    static_assert(result == value_list<t<char>, t<short>>);
}
