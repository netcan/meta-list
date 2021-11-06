//
// Created by netcan on 2021/11/5.
//

#include <catch_amalgamated.hpp>
#include <value-list/algo/transform.hpp>
#include <value-list/algo/filter.hpp>
#include <value-list/algo/fold_left.hpp>
#include <value-list/algo/append.hpp>
#include <value-list/algo/prepend.hpp>
#include <value-list/algo/concat.hpp>
#include <value-list/types/type_c.hpp>

using namespace VALUE_LIST_NS;

template<typename...>
struct dump;

TEST_CASE("value_list") {
    constexpr auto vl = value_list<>;
    SECTION("empty vl") {
        STATIC_REQUIRE(vl == value_list<>);
        STATIC_REQUIRE(vl.size() == 0);
        STATIC_REQUIRE(concepts::list<decltype(vl)>);
    }

    SECTION("from template variable") {
        constexpr auto vl = value_list<1, 2, 3, 4>;
        constexpr auto vl2 = value_list<v<1>, v<2>, v<3>, v<4>>;
        STATIC_REQUIRE(vl == vl2);
    }

    SECTION("append value") {
        constexpr auto res = append(vl, v<1>, v<2>);
        STATIC_REQUIRE(res == value_list<1, 2>);
    }

    SECTION("append type") {
        {
            constexpr auto res = vl | append(t<int>, t<double>);
            STATIC_REQUIRE(res == value_list<t<int>, t<double>>);
        }
        {
            constexpr auto res = append(vl, t<int>, t<double>);
            STATIC_REQUIRE(res == value_list<t<int>, t<double>>);
        }
    }

    SECTION("prepend value") {
        constexpr auto res = vl
                | prepend(v<1>)
                | prepend(v<2>)
                ;
        STATIC_REQUIRE(res == value_list<2, 1>);
    }

    SECTION("head & tail") {
        constexpr auto v = value_list<1, 2, 3, 4>;
        STATIC_REQUIRE(v.head() == 1);
        STATIC_REQUIRE(v.tail() == value_list<2, 3, 4>);
    }
}

TEST_CASE("adapter") {
    SECTION("transform(f)(vl)") {
        constexpr auto vl = value_list<1, 2>;
        auto res = transform([](auto x) { return x * 2; })(vl);
        STATIC_REQUIRE(res == value_list<2, 4>);
    }

    SECTION("vl | transform(f)") {
        constexpr auto vl = value_list<1, 2>;
        auto res = vl | transform([](auto x) { return x * 2; });
        STATIC_REQUIRE(res == value_list<2, 4>);
    }
}

TEST_CASE("transform") {
    SECTION("value level") {
        constexpr auto vl = value_list<1, 2, 3, 4>;
        constexpr auto result = transform(vl, [](auto x) { return x * 2; });
        STATIC_REQUIRE(result == value_list<2, 4, 6, 8>);
    }

    SECTION("type level: add_pointer_t") {
        constexpr auto vl = value_list<t<int>, t<char>, t<double>>;
        constexpr auto result = transform(vl, []<typename T>(TypeConst<T>) {
            return t<std::add_pointer_t<T>>;
        });
        STATIC_REQUIRE(result == value_list<t<int*>, t<char*>, t<double*>>);
    }

    SECTION("type level: if constexpr") {
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

TEST_CASE("filter") {
    SECTION("value level") {
        constexpr auto vl = value_list<1, 2, 3, 4>;
        constexpr auto res = vl | filter([](auto v) { return v < 3; });
        STATIC_REQUIRE(res == value_list<1, 2>);
    }

    SECTION("type level") {
        constexpr auto vl = value_list<t<int>, t<double>, t<char>, t<float>, t<char>, t<short>>;
        constexpr auto res = vl | filter([]<typename T>(TypeConst<T>) { return sizeof(T) < 4; });
        STATIC_REQUIRE(res == value_list<t<char>, t<char>, t<short>>);
    }
}

TEST_CASE("map filter") {
    constexpr auto vl = value_list<1,2,3,4,5,6,7,8,9,10>;
    constexpr auto res = vl
            | transform([](auto x) { return x * x; })
            | filter([](auto x) { return x < 10; })
            ;
    STATIC_REQUIRE(res == value_list<1,4,9>);
}

TEST_CASE("fold_left") {
    SECTION("type level") {
        constexpr auto result = value_list<t<int>, t<float>, t<double>>
                              | fold_left(value_list<>, [](concepts::list auto acc, auto elem)
                                                          { return acc | append(elem); })
                              ;
        STATIC_REQUIRE(result == value_list<t<int>, t<float>, t<double>>);
    }
}

TEST_CASE("concat") {
    constexpr auto vl = value_list<t<long>, t<char>, t<int>, t<double>, t<float>>;
    STATIC_REQUIRE(vl == concat(value_list<t<long>, t<char>>, value_list<t<int>, t<double>, t<float>>));
    STATIC_REQUIRE(vl == concat(value_list<t<long>, t<char>>, value_list<t<int>>, value_list<t<double>, t<float>>));
}

TEST_CASE("test") {
}