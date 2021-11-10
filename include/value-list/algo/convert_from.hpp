//
// Created by netcan on 2021/11/9.
//

#ifndef VALUE_LIST_CONVERT_FROM_HPP
#define VALUE_LIST_CONVERT_FROM_HPP
#include <value-list/concept/list.hpp>
#include <value-list/types/type_list.hpp>

VALUE_LIST_NS_BEGIN
template<typename T>
struct ConvertFrom;

template<template<auto...> class Target, auto... values>
struct ConvertFrom<Target<values...>> {
    consteval auto operator()() const -> concepts::list auto {
        return value_list<values...>;
    }
};

template<template<typename T, T...> class Target, typename T, auto... values>
struct ConvertFrom<Target<T, values...>> { // eg, integer_sequence
    consteval auto operator()() const -> concepts::list auto {
        return value_list<static_cast<T>(values)...>;
    }
};

template<template<typename...> class Target, typename ...Ts>
struct ConvertFrom<Target<Ts...>> {
    consteval auto operator()() const -> concepts::list auto {
        return type_list<Ts...>;
    }
};

template<typename T>
inline constexpr auto convert_from = ConvertFrom<T>{};

VALUE_LIST_NS_END
#endif //VALUE_LIST_CONVERT_FROM_HPP
