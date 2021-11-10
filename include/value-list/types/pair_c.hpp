//
// Created by netcan on 2021/11/7.
//

#ifndef VALUE_LIST_PAIR_C_HPP
#define VALUE_LIST_PAIR_C_HPP
#include <type_traits>
#include <value-list/value_list_ns.hpp>
VALUE_LIST_NS_BEGIN
template<typename F, typename S>
struct Pair {
    static constexpr F first {};
    static constexpr S second {};
//    using First = F;
//    using Second = S;
    static constexpr auto is_pair_const = true;
};

template<typename F, typename S>
inline constexpr auto pair = Pair<F, S>{};

template<typename FL, typename SL, typename FR, typename SR>
consteval bool operator==(Pair<FL, SL>, Pair<FR, SR>) {
    return std::is_same_v<FL, FR> && std::is_same_v<SL, SR>;
}

VALUE_LIST_NS_END
#endif //VALUE_LIST_PAIR_C_HPP
