//
// Created by netcan on 2021/11/8.
//

#ifndef VALUE_LIST_CONVERT_TO_HPP
#define VALUE_LIST_CONVERT_TO_HPP
#include <value-list/concept/list.hpp>
#include <value-list/types/type_c.hpp>
VALUE_LIST_NS_BEGIN
namespace detail {
template<template<auto...> class Target>
struct ConvertToTargetValues {
    template<concepts::pair_const auto... values>
    consteval auto operator()(ValueList<values...>) const -> concepts::type_const auto {
        return _t<Target<values...>>;
    }

    template<concepts::value_const auto... values>
    consteval auto operator()(ValueList<values...>) const -> concepts::type_const auto {
        return _t<Target<values.value...>>;
    }
};

template<template<typename...> class Target>
struct ConvertToTargetTypes {
    template<concepts::type_const auto... types>
    consteval auto operator()(ValueList<types...>) const -> concepts::type_const auto {
        return _t<Target<get_typ<types>...>>;
    }
};
}

template<template<auto...> class Target>
consteval auto convert_to() {
    return detail::ConvertToTargetValues<Target>{};
}

template<template<typename...> class Target>
consteval auto convert_to() {
    return detail::ConvertToTargetTypes<Target>{};
}


VALUE_LIST_NS_END
#endif //VALUE_LIST_CONVERT_TO_HPP
