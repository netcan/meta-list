//
// Created by netcan on 2021/11/5.
//

#ifndef META_LIST_VALUE_C_HPP
#define META_LIST_VALUE_C_HPP
#include <meta-list/meta_list_ns.hpp>
META_LIST_NS_BEGIN

template<auto v>
struct ValueConst {
    consteval ValueConst() = default;

    constexpr static auto value = v;
    constexpr static bool is_value_const = true;

    consteval operator decltype(v)() const {
        return v;
    }
};

template<auto value>
inline constexpr ValueConst<value> _v;

template<auto l, auto r>
consteval bool operator==(ValueConst<l>, ValueConst<r>) {
    return l == r;
}

META_LIST_NS_END
#endif //META_LIST_VALUE_C_HPP
