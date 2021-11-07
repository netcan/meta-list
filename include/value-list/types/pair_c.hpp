//
// Created by netcan on 2021/11/7.
//

#ifndef VALUE_LIST_PAIR_C_HPP
#define VALUE_LIST_PAIR_C_HPP
#include <type_traits>
#include <value-list/value_list_ns.hpp>
VALUE_LIST_NS_BEGIN
template<auto f, auto s>
struct Pair {
    static constexpr auto first = f;
    static constexpr auto second = s;
    static constexpr auto is_pair_const = true;
};

template<auto f, auto s>
inline constexpr auto pair = Pair<f, s>{};

template<auto fl, auto sl, auto fr, auto sr>
consteval bool operator==(Pair<fl, sl>, Pair<fr, sr>) {
    return fl == fr && sl == sr;
}

VALUE_LIST_NS_END
#endif //VALUE_LIST_PAIR_C_HPP
