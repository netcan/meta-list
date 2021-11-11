//
// Created by netcan on 2021/11/5.
//

#ifndef META_LIST_META_LIST_H
#define META_LIST_META_LIST_H
#include <meta-list/types/dispatch_value.hpp>
#include <meta-list/concept/value_or_type.hpp>
#include <meta-list/meta_list_ns.hpp>
#include <cstddef>
#include <tuple>
META_LIST_NS_BEGIN
template<typename... Ts>
struct TypeList {
    consteval size_t size() const { return sizeof...(Ts); }
    consteval bool empty() const { return size() == 0; }
    consteval auto head() const requires requires { this->empty(); } {
        return std::get<0>(std::make_tuple(Ts{}...));
    }
    consteval auto tail() const requires requires { this->empty(); } {
        return []<typename T, typename... Rest>(T, Rest...) {
            return TypeList<Rest...>{};
        }(Ts{}...);
    }
    constexpr static bool is_type_list = true;
};

template<typename... Ts>
inline constexpr auto type_list = TypeList<TypeConst<Ts>...>{};

template<auto... values>
inline constexpr auto value_list = TypeList<dispatch_value<values>...>{};

template<typename... lhs, typename... rhs>
consteval bool operator==(TypeList<lhs...>, TypeList<rhs...>) {
    if constexpr (sizeof...(lhs) != sizeof...(rhs)) { return false; }
//    else { return ((std::is_same_v<lhs, rhs>) && ...); } // fix gcc
    else { return ((lhs{} == rhs{}) && ...); }
}

META_LIST_NS_END
#endif //META_LIST_META_LIST_H
