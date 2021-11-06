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
    constexpr auto vl2 = value_list<v<1>, v<2>, v<3>, v<4>>;
    STATIC_REQUIRE(vl == vl2);
}

TEST_CASE("transform") {
    SECTION("calculate value") {
        constexpr auto vl = value_list<1, 2, 3, 4>;
        constexpr auto result = transform(vl, [](auto x) { return x * 2; });
        STATIC_REQUIRE(result == value_list<2, 4, 6, 8>);
    }

    SECTION("calculate type: add_pointer_t") {
        constexpr auto vl = value_list<t<int>, t<char>, t<double>>;
        constexpr auto result = transform(vl, []<typename T>(TypeConst<T>) {
            return t<std::add_pointer_t<T>>;
        });
        STATIC_REQUIRE(result == value_list<t<int*>, t<char*>, t<double*>>);
    }

    SECTION("calculate type: if constexpr") {
        constexpr auto vl = value_list<1, 2>;
        constexpr auto result = transform(vl, [](auto v) {
            if constexpr (v == 1) {
                return t<char>;
            } else if (v == 2) {
                return t<short>;
            }
        });
        STATIC_REQUIRE(result == value_list<t<char>, t<short>>);
    }
}

TEST_CASE("adapter") {
    SECTION("transform(f)(vl)") {
        constexpr auto vl = value_list<1, 2>;
        auto res = transform([](auto x) { return x * 2; })(vl);
        STATIC_REQUIRE(res == value_list<2, 4>);
    }
}
