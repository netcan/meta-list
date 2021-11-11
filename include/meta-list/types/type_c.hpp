//
// Created by netcan on 2021/11/5.
//

#ifndef META_LIST_TYPE_C_HPP
#define META_LIST_TYPE_C_HPP
#include <type_traits>
#include <meta-list/meta_list_ns.hpp>
#include <meta-list/concept/value_or_type.hpp>

META_LIST_NS_BEGIN
template<typename T>
struct TypeConst {
    using type = T;
    constexpr static bool is_type_const = true;
};

template<typename T>
inline constexpr TypeConst<T> _t;

template<concepts::type_const auto type_c>
using get_typ = typename decltype(type_c)::type;

template<typename L, typename R>
consteval bool operator==(TypeConst<L>, TypeConst<R>) {
    return std::is_same_v<L, R>;
}

META_LIST_NS_END
#endif //META_LIST_TYPE_C_HPP
