//
// Created by netcan on 2021/11/5.
//

#include <catch_amalgamated.hpp>
#include <value-list/types/type_c.hpp>
#include <value-list/types/pair_c.hpp>
#include <value-list/algorithm.hpp>

using namespace VALUE_LIST_NS;

template<auto...>
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
        constexpr auto vl2 = value_list<_v<1>, _v<2>, _v<3>, _v<4>>;
        STATIC_REQUIRE(vl == vl2);
    }

    SECTION("append value") {
        constexpr auto res = append(vl, _v<1>, _v<2>);
        STATIC_REQUIRE(res == value_list<1, 2>);
    }

    SECTION("append type") {
        {
            constexpr auto res = vl | append(_t<int>, _t<double>);
            STATIC_REQUIRE(res == value_list<_t<int>, _t<double>>);
        }
        {
            constexpr auto res = append(vl, _t<int>, _t<double>);
            STATIC_REQUIRE(res == value_list<_t<int>, _t<double>>);
        }
    }

    SECTION("prepend value") {
        constexpr auto res = vl
                | prepend(_v<1>)
                | prepend(_v<2>)
                ;
        STATIC_REQUIRE(res == value_list<2, 1>);
    }

    SECTION("prepend value list") {
        constexpr auto res = vl | prepend(value_list<1,2,3>);
        STATIC_REQUIRE(res == value_list<value_list<1,2,3>>);
    }

    SECTION("head & tail") {
        constexpr auto v = value_list<1, 2, 3, 4>;
        STATIC_REQUIRE(v.head() == 1);
        STATIC_REQUIRE(v.tail() == value_list<2, 3, 4>);
    }
}

TEST_CASE("pair") {
    SECTION("pair combine with value_list") {
        STATIC_REQUIRE(value_list<pair<1, 2>> == value_list<pair<1, 2>>);
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
        constexpr auto vl = value_list<_t<int>, _t<char>, _t<double>>;
        constexpr auto result = transform(vl, []<typename T>(TypeConst<T>) {
            return _t<std::add_pointer_t<T>>;
        });
        STATIC_REQUIRE(result == value_list<_t<int*>, _t<char*>, _t<double*>>);
    }

    SECTION("type level: if constexpr") {
        constexpr auto vl = value_list<1, 2>;
        constexpr auto result = transform(vl, [](auto v) {
            if constexpr (v == 1) {
                return _t<char>;
            } else if (v == 2) {
                return _t<short>;
            }
        });
        STATIC_REQUIRE(result == value_list<_t<char>, _t<short>>);
    }
}

TEST_CASE("filter") {
    SECTION("value level") {
        constexpr auto vl = value_list<1, 2, 3, 4>;
        constexpr auto res = vl | filter([](auto v) { return v < 3; });
        STATIC_REQUIRE(res == value_list<1, 2>);
    }

    SECTION("type level") {
        constexpr auto vl = value_list<_t<int>, _t<double>, _t<char>, _t<float>, _t<char>, _t<short>>;
        constexpr auto res = vl | filter([]<typename T>(TypeConst<T>) { return sizeof(T) < 4; });
        STATIC_REQUIRE(res == value_list<_t<char>, _t<char>, _t<short>>);
    }
}

TEST_CASE("map filter fold") {
    constexpr auto vl = value_list<1,2,3,4,5,6,7,8,9,10>;
    constexpr auto res = vl
            | transform([](auto x) { return x * x; })
            | filter([](auto x) { return x < 30; })
            | fold_left(0, [](auto acc, auto n) { return acc + n; })
            ;
    STATIC_REQUIRE(res == 55);
}

TEST_CASE("fold_left") {
    SECTION("type level") {
        constexpr auto result = value_list<_t<int>, _t<float>, _t<double>>
                              | fold_left(value_list<>, [](concepts::list auto acc, auto elem)
                                                          { return acc | append(elem); })
                              ;
        STATIC_REQUIRE(result == value_list<_t<int>, _t<float>, _t<double>>);
    }
}

TEST_CASE("concat") {
    constexpr auto vl = value_list<_t<long>, _t<char>, _t<int>, _t<double>, _t<float>>;
    STATIC_REQUIRE(vl == concat(value_list<_t<long>, _t<char>>, value_list<_t<int>, _t<double>, _t<float>>));
    STATIC_REQUIRE(vl == concat(value_list<_t<long>, _t<char>>, value_list<_t<int>>, value_list<_t<double>, _t<float>>));
}

TEST_CASE("partition") {
    constexpr auto result =
            value_list<_t<int>, _t<long long>, _t<char>, _t<float>, _t<short>, _t<double>, _t<bool>, _t<long double>>
            | partition([]<typename T>(TypeConst<T>) {
                return sizeof(T) < 8;
            });
    STATIC_REQUIRE(result.first == value_list<_t<int>, _t<char>, _t<float>, _t<short>, _t<bool>>);
    STATIC_REQUIRE(result.second == value_list<_t<long long>, _t<double>, _t<long double>>);
}

TEST_CASE("contain") {
    SECTION("type level") {
        constexpr auto vl = value_list<_t<int>, _t<char>, _t<float>, _t<short>>;
        STATIC_REQUIRE(contain(vl, _t<int>));
        STATIC_REQUIRE(!contain(vl, _t<long long>));
    }
    SECTION("value level") {
        constexpr auto vl = value_list<1,2,3,4>;
        STATIC_REQUIRE(contain(vl, 2));
        STATIC_REQUIRE(!contain(vl, 0));
    }
}

TEST_CASE("unique") {
    SECTION("type level") {
        constexpr auto vl = unique(value_list<_t<int>, _t<int>, _t<float>, _t<short>>);
        STATIC_REQUIRE(vl == value_list<_t<int>, _t<float>, _t<short>>);
    }
    SECTION("value level") {
        constexpr auto vl = value_list<1,1,1,1,1,2,1> | unique();
        STATIC_REQUIRE(vl == value_list<2, 1>);
    }
}

TEST_CASE("test") {
}