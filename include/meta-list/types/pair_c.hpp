//
// Created by netcan on 2021/11/7.
//

#ifndef META_LIST_PAIR_C_HPP
#define META_LIST_PAIR_C_HPP
#include <type_traits>
#include <meta-list/meta_list_ns.hpp>
META_LIST_NS_BEGIN
template<typename F, typename S>
struct Pair {
    static constexpr F first {};
    static constexpr S second {};
//    using First = F;
//    using Second = S;
    static constexpr auto is_pair_const = true;
};

template<typename F, typename S>
consteval auto make_pair(F, S) -> Pair<F, S> { return {}; }

template<typename FL, typename SL, typename FR, typename SR>
consteval bool operator==(Pair<FL, SL>, Pair<FR, SR>) {
    return std::is_same_v<FL, FR> && std::is_same_v<SL, SR>;
}

META_LIST_NS_END
#endif //META_LIST_PAIR_C_HPP
