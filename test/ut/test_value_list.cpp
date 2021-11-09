//
// Created by netcan on 2021/11/5.
//

#include <catch_amalgamated.hpp>
#include <value-list/type.hpp>
#include <value-list/algorithm.hpp>
#include <vector>
#include <variant>

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
            STATIC_REQUIRE(res == type_list<int, double>);
        }
        {
            constexpr auto res = append(vl, _t<int>, _t<double>);
            STATIC_REQUIRE(res == type_list<int, double>);
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
        constexpr auto vl = type_list<int, char, double>;
        constexpr auto result = transform(vl, []<typename T>(TypeConst<T>) {
            return _t<std::add_pointer_t<T>>;
        });
        STATIC_REQUIRE(result == type_list<int*, char*, double*>);
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
        STATIC_REQUIRE(result == type_list<char, short>);
    }
}

TEST_CASE("filter") {
    SECTION("value level") {
        constexpr auto vl = value_list<1, 2, 3, 4>;
        constexpr auto res = vl | filter([](auto v) { return v < 3; });
        STATIC_REQUIRE(res == value_list<1, 2>);
    }

    SECTION("type level") {
        constexpr auto vl = type_list<int, double, char, float, char, short>;
        constexpr auto res = vl | filter([]<typename T>(TypeConst<T>) { return sizeof(T) < 4; });
        STATIC_REQUIRE(res == type_list<char, char, short>);
    }
}

TEST_CASE("map filter fold") {
    SECTION("value level") {
        constexpr auto res = value_list<1,2,3,4,5,6,7,8,9,10>
                           | transform([](auto x) { return x * x; })
                           | filter([](auto x) { return x < 30; })
                           | fold_left(0, [](auto acc, auto n) { return acc + n; })
                           ;
        STATIC_REQUIRE(res == 55);
    }


    SECTION("type level: add_pointer_t") {
        constexpr auto result = type_list<int, char, long, char, short, float, double>
                            | filter([]<typename T>(TypeConst<T>) { return sizeof(T) < 4; })
                            | transform([]<typename T>(TypeConst<T>) { return _t<std::add_pointer_t<T>>; })
                            | unique()
                            | convert_to<std::variant>()
                            ;
        STATIC_REQUIRE(result == _t<std::variant<char*, short*>>);
    }
}

TEST_CASE("fold_left") {
    SECTION("type level") {
        constexpr auto result = type_list<int, float, double>
                              | fold_left(type_list<>, [](concepts::list auto acc, auto elem)
                                                         { return acc | append(elem); })
                              ;
        STATIC_REQUIRE(result == type_list<int, float, double>);
    }
}

TEST_CASE("concat") {
    constexpr auto vl = type_list<long, char, int, double, float>;
    STATIC_REQUIRE(vl == concat(type_list<long, char>, type_list<int, double, float>));
    STATIC_REQUIRE(vl == concat(type_list<long, char>, type_list<int>, type_list<double, float>));
}

TEST_CASE("partition") {
    constexpr auto result =
            type_list<int, long long, char, float, short, double, bool, long double>
            | partition([]<typename T>(TypeConst<T>) {
                return sizeof(T) < 8;
            });
    STATIC_REQUIRE(result.first == type_list<int, char, float, short, bool>);
    STATIC_REQUIRE(result.second == type_list<long long, double, long double>);
}

TEST_CASE("contain") {
    SECTION("type level") {
        constexpr auto vl = type_list<int, char, float, short>;
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
        constexpr auto vl = unique(type_list<int, int, float, short>);
        STATIC_REQUIRE(vl == type_list<int, float, short>);
    }
    SECTION("value level") {
        constexpr auto vl = value_list<1,1,1,1,1,2,1> | unique();
        STATIC_REQUIRE(vl == value_list<2, 1>);
    }
}

TEST_CASE("enumerate") {
    constexpr auto vl = value_list<_t<int>, _t<float>, _t<short>> | enumerate();
    STATIC_REQUIRE(vl == value_list<pair<0, _t<int>>, pair<1, _t<float>>, pair<2, _t<short>>>);
}

TEST_CASE("flatten") {
    constexpr auto vl = value_list<
            value_list<1,value_list<2>,3>,
            value_list<4,5,6>,
            value_list<7,8,9>>
            | flatten();
    STATIC_REQUIRE(vl == value_list<1,2,3,4,5,6,7,8,9>);
}

TEST_CASE("convert_to") {
    SECTION("value level") {
        constexpr auto res = value_list<1,3,5,7,9>
                           | convert_to<std::index_sequence>()
                           ;
        STATIC_REQUIRE(res == _t<std::index_sequence<1,3,5,7,9>>);
    }

    SECTION("type level: tuple") {
        constexpr auto res = type_list<int, char, double>
                           | convert_to<std::tuple>()
                           ;
        STATIC_REQUIRE(res == _t<std::tuple<int, char, double>>);
    }

    SECTION("type level: vector") {
        constexpr auto res = type_list<int, std::allocator<int>>
                           | convert_to<std::vector>();
        STATIC_REQUIRE(res == _t<std::vector<int, std::allocator<int>>>);
    }
}

TEST_CASE("convert_from") {
    SECTION("value level") {
        constexpr auto vl = convert_from<std::make_index_sequence<10>>();
        STATIC_REQUIRE(vl == value_list<0,1,2,3,4,5,6,7,8,9>);
    }
    SECTION("type level") {
        constexpr auto vl = convert_from<std::tuple<int, char, double>>();
        STATIC_REQUIRE(vl == type_list<int, char, double>);
    }
}

TEST_CASE("test") {
}