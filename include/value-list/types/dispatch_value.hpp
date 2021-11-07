//
// Created by netcan on 2021/11/5.
//

#ifndef VALUE_LIST_DISPATCH_VALUE_HPP
#define VALUE_LIST_DISPATCH_VALUE_HPP
#include <value-list/types/type_c.hpp>
#include <value-list/types/value_c.hpp>
#include <value-list/concept/value_or_type.hpp>
#include <value-list/concept/list.hpp>
#include <value-list/value_list_ns.hpp>
VALUE_LIST_NS_BEGIN

template<auto value>
inline constexpr auto dispatch_value = _v<value>;

template<concepts::value_const auto value>
inline constexpr auto dispatch_value<value> = dispatch_value<value.value>;

template<concepts::list auto value>
inline constexpr auto dispatch_value<value> = value;

template<concepts::type_const auto value>
inline constexpr auto dispatch_value<value> = value;

VALUE_LIST_NS_END
#endif //VALUE_LIST_DISPATCH_VALUE_HPP
