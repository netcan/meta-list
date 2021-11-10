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
    template<concepts::type_const... Types>
    consteval auto operator()(TypeList<Types...>) const -> concepts::type_const auto {
        return _t<Target<Types::type...>>;
    }

    template<concepts::value_const... Values>
    consteval auto operator()(TypeList<Values...>) const -> concepts::type_const auto {
        return _t<Target<Values::value...>>;
    }
};

template<template<typename...> class Target>
struct ConvertToTargetTypes {
    template<concepts::type_const... Types>
    consteval auto operator()(TypeList<Types...>) const -> concepts::type_const auto {
        return _t<Target<typename Types::type...>>;
    }

    template<typename ... Types>
    consteval auto operator()(TypeList<Types...>) const -> concepts::type_const auto {
        return _t<Target<Types...>>;
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
